#include "PhysicsList.hh"


#include "G4UnitsTable.hh"


#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4VUserPhysicsList.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4EmParameters.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ProcessManager.hh"
#include "G4LossTableManager.hh"
#include "G4EmProcessOptions.hh"

// gamma
#include "G4PhotoElectricEffect.hh"
//
//#include "G4PenelopePhotoElectricModel.hh"
#include "G4GammaConversion.hh"
//
//#include "G4PenelopeGammaConversionModel.hh"
#include "G4ComptonScattering.hh"
#include "G4RayleighScattering.hh"
//
//#include "G4PenelopeRayleighModel.hh"
#include "G4PenelopeComptonModel.hh"
// Adding penelop model
//#include "G4LivermoreComptonModel.hh"
//#include "G4KleinNishinaCompton.hh"

// electrons
#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"
//
//#include "G4PenelopeIonisationModel.hh"
//#include "G4PenelopeBremsstrahlungModel.hh"
// hadrons
#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"
//
//#include "G4PenelopeAnnihilationModel.hh"
#include "G4ionIonisation.hh"
#include "G4NuclearStopping.hh"

// ions
#include "G4DecayPhysics.hh"
#include "G4NuclideTable.hh"

#include "G4IonConstructor.hh"
#include "G4RadioactiveDecay.hh"
#include "G4RadioactiveDecayPhysics.hh"

#include "G4UAtomicDeexcitation.hh"

#include "G4HadronElasticPhysicsHP.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4HadronPhysicsINCLXX.hh"
#include "G4IonElasticPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4IonINCLXXPhysics.hh"

// particles

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"




PhysicsList::PhysicsList () :G4VModularPhysicsList()
{
    G4int verb = 1;
    SetVerboseLevel(verb);
    
    //add new units for radioActive decays
    //
    new G4UnitDefinition( "millielectronVolt", "meV", "Energy", 1.e-3*eV);   
    // 
    const G4double minute = 60*second;
    const G4double hour   = 60*minute;
    const G4double day    = 24*hour;
    const G4double year   = 365*day;
    new G4UnitDefinition("minute", "min", "Time", minute);
    new G4UnitDefinition("hour",   "h",   "Time", hour);
    new G4UnitDefinition("day",    "d",   "Time", day);
    new G4UnitDefinition("year",   "y",   "Time", year);
    
    // Mandatory for G4NuclideTable
    // Half-life threshold must be set small or many short-lived isomers 
    // will not be assigned life times (default to 0) 
    G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(0.1*picosecond);
    G4NuclideTable::GetInstance()->SetLevelTolerance(1.0*eV);
    
    // EM physics
    RegisterPhysics(new G4EmStandardPhysics());
    G4EmParameters* param = G4EmParameters::Instance();
    param->SetAugerCascade(true);
    param->SetStepFunction(1., 1*CLHEP::mm);
    param->SetStepFunctionMuHad(1., 1*CLHEP::mm);
    
    // Decay
    RegisterPhysics(new G4DecayPhysics());
    
    // Radioactive decay
    RegisterPhysics(new G4RadioactiveDecayPhysics());
      // Hadron Elastic scattering
    RegisterPhysics( new G4HadronElasticPhysicsHP(verb) );
    
    // Hadron Inelastic physics
    RegisterPhysics( new G4HadronPhysicsFTFP_BERT_HP(verb));
    ////RegisterPhysics( new G4HadronPhysicsQGSP_BIC_HP(verb));
    ////RegisterPhysics( new G4HadronInelasticQBBC(verb));        
    ////RegisterPhysics( new G4HadronPhysicsINCLXX(verb));
    
    // Ion Elastic scattering
    RegisterPhysics( new G4IonElasticPhysics(verb));
    
    // Ion Inelastic physics
    RegisterPhysics( new G4IonPhysics(verb));
    ////RegisterPhysics( new G4IonINCLXXPhysics(verb));
    
    // Gamma-Nuclear Physics
    //G4EmExtraPhysics* gnuc = new G4EmExtraPhysics(verb);
  
}

PhysicsList::~PhysicsList ()
{
}

void PhysicsList::ConstructParticle ()
{
  // geantino
  G4Geantino::GeantinoDefinition();

  // gamma
  G4Gamma::GammaDefinition();

  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();

  // baryons
  G4Proton::ProtonDefinition();
  G4Neutron::NeutronDefinition();

  // ions
  G4IonConstructor iConstructor;
  iConstructor.ConstructParticle();
}

void PhysicsList::ConstructProcess ()
{
  AddTransportation();
  ConstructEM();
  ConstructRD();
}

void PhysicsList::ConstructEM ()
{
  auto theParticleIterator=GetParticleIterator();

  theParticleIterator->reset();
  while((*theParticleIterator)()) {

    G4ParticleDefinition* particle = theParticleIterator->value();

    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    if (particleName == "gamma") {


      //G4PhotoElectricEffect* thePhotoElectricEffect = new G4PhotoElectricEffect();
      //thePhotoElectricEffect->SetModel(new G4PenelopePhotoElectricModel());
      //pmanager->AddDiscreteProcess(thePhotoElectricEffect);
      //G4GammaConversion* theGammaConversion = new G4GammaConversion();
      //theGammaConversion->SetModel(new G4PenelopeGammaConversionModel());
      //pmanager->AddDiscreteProcess(theGammaConversion);
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
      /*////pmanager->AddDiscreteProcess(new G4LowEnergyCompton);*/
      pmanager->AddDiscreteProcess(new G4GammaConversion);
      G4ComptonScattering* theComptonScattering = new G4ComptonScattering();
      theComptonScattering->SetEmModel(new G4PenelopeComptonModel());
      //theComptonScattering->SetModel(new G4LivermoreComptonModel());
      pmanager->AddDiscreteProcess(theComptonScattering);
      //pmanager->AddDiscreteProcess(new G4ComptonScattering);

    } else if (particleName == "e-") {
     /*
      pmanager->AddProcess(new G4eMultipleScattering(), -1, 1, 1);
      //pmanager->AddProcess(new G4eIonisation,           -1, 2, 2);
      G4eIonisation* theIonisation = new G4eIonisation();
      theIonisation->SetEmModel(new G4PenelopeIonisationModel());
      pmanager->AddProcess(theIonisation,-1,1,1);
      //pmanager->AddProcess(new G4eBremsstrahlung(),     -1,-3, 3);
      G4eBremsstrahlung* theBremsstrahlung = new G4eBremsstrahlung();
      theBremsstrahlung->SetEmModel(new G4PenelopeBremsstrahlungModel());
      pmanager->AddProcess(theBremsstrahlung, -1, -3, 3);*/
      pmanager->AddProcess(new G4eMultipleScattering(), -1, 1, 1);
      pmanager->AddProcess(new G4eIonisation,           -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung(),     -1,-3, 3);

    } else if (particleName == "e+") {
      /*
      pmanager->AddProcess(new G4eMultipleScattering(), -1, 1, 1);
      //pmanager->AddProcess(new G4eIonisation,           -1, 2, 2);
      G4eIonisation* theIonisation = new G4eIonisation();
      theIonisation->SetEmModel(new G4PenelopeIonisationModel());
      pmanager->AddProcess(theIonisation,-1,1,1);
      //pmanager->AddProcess(new G4eBremsstrahlung,       -1,-3, 3);
      G4eBremsstrahlung* theBremsstrahlung = new G4eBremsstrahlung();
      theBremsstrahlung->SetEmModel(new G4PenelopeBremsstrahlungModel());
      pmanager->AddProcess(theBremsstrahlung, -1, -3, 3);
      pmanager->AddProcess(new G4eplusAnnihilation,      0,-1, 4);*/
      pmanager->AddProcess(new G4eMultipleScattering(), -1, 1, 1);
      pmanager->AddProcess(new G4eIonisation,           -1, 2, 2);
      pmanager->AddProcess(new G4eBremsstrahlung,       -1,-3, 3);
      pmanager->AddProcess(new G4eplusAnnihilation,      0,-1, 4);

    } else if (particleName == "alpha" ||
	       particleName == "He3") {

      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4ionIonisation,       -1, 2, 2);
      pmanager->AddProcess(new G4NuclearStopping(),   -1, 3,-1);

    } else if (particleName == "GenericIon") {

      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4ionIonisation,       -1, 2, 2);
      pmanager->AddProcess(new G4NuclearStopping(),   -1, 3,-1);

    } else if (particleName == "proton" ) {

      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);
      pmanager->AddProcess(new G4hBremsstrahlung,     -1,-3, 3);
      pmanager->AddProcess(new G4hPairProduction,     -1,-4, 4);

    } else if (particleName == "charged-geantino" ||
	       particleName == "geantino") {

      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);

    }
  }
  G4EmProcessOptions opt;
  opt.SetPolarAngleLimit(0.2);
  // ADDING MINIMUM LIMIT TO 1eV
  opt.SetMinEnergy(0.02*keV);
  opt.SetMaxEnergy(100.*GeV);
}

void PhysicsList::ConstructRD()
{
  G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay();
  radioactiveDecay->SetHLThreshold(-1.*s);
  radioactiveDecay->SetICM(true);
  radioactiveDecay->SetARM(false);
  G4ProcessManager* pmanager = G4GenericIon::GenericIon()->GetProcessManager();
  pmanager->AddProcess(radioactiveDecay, 0, -1, 1);

  G4VAtomDeexcitation* de = new G4UAtomicDeexcitation();
  G4LossTableManager::Instance()->SetAtomDeexcitation(de);
}

void PhysicsList::SetCuts ()
{
  SetCutsWithDefault();
}
