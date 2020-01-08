#include "PhysicsList.hh"

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
#include "G4IonConstructor.hh"
#include "G4RadioactiveDecay.hh"
#include "G4UAtomicDeexcitation.hh"

PhysicsList::PhysicsList ()
{
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
      theComptonScattering->SetModel(new G4PenelopeComptonModel());
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
