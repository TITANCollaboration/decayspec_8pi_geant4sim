#include "SiliconDetector.hh"
#include "Randomize.hh"

SiliconDetector::SiliconDetector()
{
  response = false;
  A = 0.;
  B = 0.;
  C = 0.;
}

SiliconDetector::~SiliconDetector()
{}

G4double SiliconDetector::DetectorResponse(G4double val)
{
  if (response) {
    G4double r1, r2;
    // calculate FWHM for this energy
    //
    G4double x = val / keV;
    G4double dev = std::sqrt(std::abs(A + B*x + C*x*x)) / 2.35;
    // determine random fluctuation based on FWHM
    //
    while (true) {
      r1 = G4RandGauss::shoot(0, dev);
      G4double testval = std::pow(r1, 2.) / std::pow(dev, 2.);
      G4double probval = std::exp(-1. * testval / 2);
      r2 = G4UniformRand();
      if (r2 <= probval) break;
    }
    r1 *= keV;
    return val + r1;
  } else {
    // do nothing
    //
    return val;
  }
}
