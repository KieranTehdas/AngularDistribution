



#include "RunAction.hh"
#include "G4Run.hh"
#include "Analysis.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <assert.h>

//--------------------------------

RunAction::RunAction()
 : G4UserRunAction()
{  

	//Create an analysis manager
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();


	analysisManager->CreateNtuple("Test", "AngularDist");
	analysisManager->CreateNtupleDColumn("energyLoss");
/*
	analysisManager->CreateNtupleDColumn("ThetaScat");
	analysisManager->CreateNtupleDColumn("PhiScat");
	analysisManager->CreateNtupleDColumn("ThetaInit");
	analysisManager->CreateNtupleDColumn("PhiInit");
	*/
	analysisManager->FinishNtuple();

	//analysisManager->CreateH1("0", "Energy Angular Distribution", 180, 0.0, 50.0*MeV);

	
	analysisManager->CreateH2("EnergyDepend", "Energy Loss Dependence on Vertex Energy", 
		200.0, 0.0, 200*MeV, 1000.0, 0.0, 100.0*MeV);

}

//-- -- -- -- -- -- -- -- -- -- --

RunAction::~RunAction()
{
	delete G4AnalysisManager::Instance(); 
}

//-- -- -- -- -- -- -- -- -- -- --

void RunAction::BeginOfRunAction(const G4Run*)
{ 
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  G4String fileName = "AngularEnergyDistribution";
  analysisManager->OpenFile(fileName);
}

//-- -- -- -- -- -- -- -- -- -- --

void RunAction::EndOfRunAction(const G4Run* )
{

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

	// save ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();
}