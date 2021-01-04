//Adapted from https://github.com/lmoneta/tmva-tutorial  

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"

int TMVAClassification( TString myMethodList = "" )
{
   int readnorm = 1;
	
   TMVA::Tools::Instance();

   std::map<std::string,int> Use;

   // Cut optimisation
   Use["Cuts"]            = 0;
   Use["CutsD"]           = 0;
   Use["CutsPCA"]         = 0;
   Use["CutsGA"]          = 0;
   Use["CutsSA"]          = 0;
   //
   // 1-dimensional likelihood ("naive Bayes estimator")
   Use["Likelihood"]      = 0;
   Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
   Use["LikelihoodPCA"]   = 0; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
   Use["LikelihoodKDE"]   = 0;
   Use["LikelihoodMIX"]   = 0;
   //
   // Mutidimensional likelihood and Nearest-Neighbour methods
   Use["PDERS"]           = 0;
   Use["PDERSD"]          = 0;
   Use["PDERSPCA"]        = 0;
   Use["PDEFoam"]         = 0;
   Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
   Use["KNN"]             = 0; // k-nearest neighbour method
   //
   // Linear Discriminant Analysis
   Use["LD"]              = 0; // Linear Discriminant identical to Fisher
   Use["Fisher"]          = 0;
   Use["FisherG"]         = 0;
   Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
   Use["HMatrix"]         = 0;
   //
   // Function Discriminant analysis
   Use["FDA_GA"]          = 0; // minimisation of user-defined function using Genetics Algorithm
   Use["FDA_SA"]          = 0;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   Use["FDA_MCMT"]        = 0;
   //
   // Neural Networks (all are feed-forward Multilayer Perceptrons)
   Use["MLP"]             = 1; // Recommended ANN
   Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
   Use["MLPBNN"]          = 0; // Recommended ANN with BFGS training method and bayesian regulator
   Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
   Use["TMlpANN"]         = 0; // ROOT's own ANN
#ifdef R__HAS_TMVAGPU
   Use["DNN_GPU"]         = 0; // CUDA-accelerated DNN training.
#else
   Use["DNN_GPU"]         = 0;
#endif

#ifdef R__HAS_TMVACPU
   Use["DNN_CPU"]         = 1; // Multi-core accelerated DNN.
#else
   Use["DNN_CPU"]         = 0;
#endif
   //
   // Support Vector Machine
   Use["SVM"]             = 0;
   //
   // Boosted Decision Trees
   Use["BDT"]             = 1; // uses Adaptive Boost
   Use["BDTG"]            = 0; // uses Gradient Boost
   Use["BDTB"]            = 0; // uses Bagging
   Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
   Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting
   //
   // Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
   Use["RuleFit"]         = 0;
   // ---------------------------------------------------------------

   std::cout << std::endl;
   std::cout << "==> Start TMVAClassification" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return 1;
         }
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   // Here the preparation phase begins

   // Read training and test data
   // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
   TFile *input(0);
//   TString fname = "./tmva_class_example.root";
   TString fname = "MC13TeV_2017_TAToTTQ_MA-scan_TuneCP5_13TeV_G2HDM-rtc04.root";
   cout<<fname<<endl;
   if (!gSystem->AccessPathName( fname )) {
      input = TFile::Open( fname ); // check if file in local directory exists
   }
/*
   else {
      TFile::SetCacheFileDir(".");
      input = TFile::Open("http://root.cern.ch/files/tmva_class_example.root", "CACHEREAD");
   }
*/
   if (!input) {
      std::cout << "ERROR: could not open signal data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVAClassification       : Using input signal file: " << input->GetName() << std::endl;

   // Register the training and test trees
   TTree *signalTree     = (TTree*)input->Get("TreeInput");//Tree300,350,400,500,600,700
   
   TH1F *h_pt_l1 = new TH1F("h_pt_l1","pt(l1) (signal)",40,30,430);
   if (readnorm == 1){ 
   	float t_pt_l1,t_weight,t_scan_mass;
   	signalTree->SetBranchAddress("t_pt_l1",&t_pt_l1);
   	signalTree->SetBranchAddress("t_weight",&t_weight);
	signalTree->SetBranchAddress("t_scan_mass",&t_scan_mass);
   	Int_t nentries = (Int_t)signalTree->GetEntries();
   	for (Int_t i=0; i<nentries; i++){
	   signalTree->GetEntry(i);
	   if (t_scan_mass == 300) h_pt_l1->Fill(t_pt_l1,t_weight);
   	}
   }
   
   TString fname2 = "MC13TeV_2017_TTJets.root";
 //  TString fname2 = "MC13TeV_2017_TTJets_no_negative_weights.root";
   if (!gSystem->AccessPathName( fname2 )) {
      input = TFile::Open( fname2 ); // check if file in local directory exists
   }
   if (!input) {
      std::cout << "ERROR: could not open background data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVAClassification       : Using input background file: " << input->GetName() << std::endl;

   TTree *ttj     = (TTree*)input->Get("TreeInput");
  
   TH1F *h_pt_l1_ttj = new TH1F("h_pt_l1_ttj","pt(l1) (ttj)",40,30,430);
   if (readnorm == 1){  
      float t_pt_l1,t_weight,t_scan_mass;
	  ttj->SetBranchAddress("t_pt_l1",&t_pt_l1);
   	  ttj->SetBranchAddress("t_weight",&t_weight);
      Int_t nentries = (Int_t)ttj->GetEntries();
      for (Int_t i=0; i<nentries; i++){
	   ttj->GetEntry(i);
	   h_pt_l1_ttj->Fill(t_pt_l1,t_weight);//!!!!!!!!
   	  }
   }
   
   /*
   TString fname2_noneg = "MC13TeV_2017_TTJets_no_negative_weights.root";
   if (!gSystem->AccessPathName( fname2_noneg )) {
      input = TFile::Open( fname2_noneg ); // check if file in local directory exists
   }
   if (!input) {
      std::cout << "ERROR: could not open background data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVAClassification       : Using input background file: " << input->GetName() << std::endl;

   TTree *ttj_noneg     = (TTree*)input->Get("TreeInput");
   */
   
//-----------
   TString fname6 = "MC13TeV_2017_TTWJetsToLNu.root";
   if (!gSystem->AccessPathName( fname6 )) {
      input = TFile::Open( fname6 ); // check if file in local directory exists
   }
   if (!input) {
      std::cout << "ERROR: could not open background data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVAClassification       : Using input background file: " << input->GetName() << std::endl;

   TTree *ttWjets     = (TTree*)input->Get("TreeInput");
   
   TH1F *h_pt_l1_ttW = new TH1F("h_pt_l1_ttW","pt(l1) (ttW)",40,30,430);
   if (readnorm == 1){  
      float t_pt_l1,t_weight;
	  ttWjets->SetBranchAddress("t_pt_l1",&t_pt_l1);
   	  ttWjets->SetBranchAddress("t_weight",&t_weight);
      Int_t nentries = (Int_t)ttWjets->GetEntries();
      for (Int_t i=0; i<nentries; i++){
	   ttWjets->GetEntry(i);
	   h_pt_l1_ttW->Fill(t_pt_l1,t_weight);
   	  }
   }
//-----------

//-----------
   TString fname7 = "MC13TeV_2017_TTZToLLNuNu.root";
   if (!gSystem->AccessPathName( fname7 )) {
      input = TFile::Open( fname7 ); // check if file in local directory exists
   }
   if (!input) {
      std::cout << "ERROR: could not open background data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVAClassification       : Using input background file: " << input->GetName() << std::endl;

   TTree *ttZ     = (TTree*)input->Get("TreeInput");
   
   TH1F *h_pt_l1_ttZ = new TH1F("h_pt_l1_ttZ","pt(l1) (ttZ)",40,30,430);
   if (readnorm == 1){  
      float t_pt_l1,t_weight;
	  ttZ->SetBranchAddress("t_pt_l1",&t_pt_l1);
   	  ttZ->SetBranchAddress("t_weight",&t_weight);
      Int_t nentries = (Int_t)ttZ->GetEntries();
      for (Int_t i=0; i<nentries; i++){
	   ttZ->GetEntry(i);
	   h_pt_l1_ttZ->Fill(t_pt_l1,t_weight);
   	  }
   }
//-----------

//-----------
   TString fname11 = "MC13TeV_2017_tZq_ll.root";
   if (!gSystem->AccessPathName( fname11 )) {
      input = TFile::Open( fname11 ); // check if file in local directory exists
   }
   if (!input) {
      std::cout << "ERROR: could not open background data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVAClassification       : Using input background file: " << input->GetName() << std::endl;

   TTree *tZq     = (TTree*)input->Get("TreeInput");
   
   TH1F *h_pt_l1_tZq = new TH1F("h_pt_l1_tZq","pt(l1) (tZq)",40,30,430);
   if (readnorm == 1){  
      float t_pt_l1,t_weight;
	  tZq->SetBranchAddress("t_pt_l1",&t_pt_l1);
   	  tZq->SetBranchAddress("t_weight",&t_weight);
      Int_t nentries = (Int_t)tZq->GetEntries();
      for (Int_t i=0; i<nentries; i++){
	   tZq->GetEntry(i);
	   h_pt_l1_tZq->Fill(t_pt_l1,t_weight);
   	  }
   }
//-----------

   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
   TString outfileName( "TMVA.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   // All TMVA output can be suppressed by removing the "!" (not) in
   // front of the "Silent" argument in the option string
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
   // If you wish to modify default settings
   // (please check "src/Config.h" to see all available global options)
   //
   //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
   //    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";

   // Define the input variables that shall be used for the MVA training
   // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
   // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]
   /*
   dataloader->AddVariable( "myvar1 := var1+var2", 'F' );
   dataloader->AddVariable( "myvar2 := var1-var2", "Expression 2", "", 'F' );
   dataloader->AddVariable( "var3",                "Variable 3", "units", 'F' );
   dataloader->AddVariable( "var4",                "Variable 4", "units", 'F' );
   */
   
   
   dataloader->AddVariable( "CvsL1", "CvsL1", "units", 'F' );
   dataloader->AddVariable( "CvsB1", "CvsB1", "units", 'F' );
   dataloader->AddVariable( "CvsL2", "CvsL2", "units", 'F' );
   dataloader->AddVariable( "CvsB2", "CvsB2", "units", 'F' );
   dataloader->AddVariable( "CvsL3", "CvsL3", "units", 'F' );
   dataloader->AddVariable( "CvsB3", "CvsB3", "units", 'F' );
   dataloader->AddVariable( "t_m_lep_jet1", "t_m_lep_jet1", "GeV", 'F' );
   dataloader->AddVariable( "t_HT", "t_HT", "GeV", 'F' );
   dataloader->AddVariable( "t_dphi_ll", "t_dphi_ll", "units", 'F' );
   dataloader->AddVariable("t_pt_l1", "t_pt_l1","GeV",'F');
   dataloader->AddVariable("t_pt_l2", "t_pt_l2","GeV",'F');
   dataloader->AddVariable("t_eta_l1", "t_eta_l1","",'F');
   dataloader->AddVariable("t_eta_l2", "t_eta_l2","",'F');
   dataloader->AddVariable("t_phi_l1", "t_phi_l1","",'F');
   dataloader->AddVariable("t_phi_l2", "t_phi_l2","",'F');
   dataloader->AddVariable("t_pt_j1", "t_pt_j1","GeV",'F');
   dataloader->AddVariable("t_pt_j2", "t_pt_j2","GeV",'F');
   dataloader->AddVariable("t_pt_j3", "t_pt_j3","GeV",'F');
   dataloader->AddVariable("t_eta_j1", "t_eta_j1","",'F');
   dataloader->AddVariable("t_eta_j2", "t_eta_j2","",'F');
   dataloader->AddVariable("t_eta_j3", "t_eta_j3","",'F');
   dataloader->AddVariable("t_phi_j1", "t_phi_j1","",'F');
   dataloader->AddVariable("t_phi_j2", "t_phi_j2","",'F');
   dataloader->AddVariable("t_phi_j3", "t_phi_j3","",'F');    	   
   //dataloader->AddVariable( "t_deepcsv", "t_deepcsv", "units", 'F' );
   //dataloader->AddVariable( "t_m_lep_bottom",       "t_m_lep_bottom", "GeV", 'F' );

	   
   dataloader->SetSignalWeightExpression("t_weight");
   dataloader->SetBackgroundWeightExpression("t_weight" );

   /*
   dataloader->AddVariable( "btag1",                "btag1", "units", 'I' );
   dataloader->AddVariable( "btag2",                "btag2", "units", 'I' );
   dataloader->AddVariable( "btag3",                "btag3", "units", 'I' );
   */

   // You can add so-called "Spectator variables", which are not used in the MVA training,
   // but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the
   // input variables, the response values of all trained MVAs, and the spectator variables

   /*
   dataloader->AddSpectator( "spec1 := btag1",  "Spectator 1", "units", 'F' );
   dataloader->AddSpectator( "spec2 := btag2",  "Spectator 2", "units", 'F' );
   dataloader->AddSpectator( "spec3 := btag3",  "Spectator 2", "units", 'F' );
   */
   cout<<"TEST POINT1"<<endl;


   // global event weights per tree (see below for setting event-wise weights)
   Double_t lumi = 41367.0;
   Double_t signalWeight = lumi*0.043264 ;
   Double_t ttjWeight = lumi*832.;
   Double_t ttWWeight = lumi*0.2198;
   Double_t ttZWeight = lumi*0.2432;
   Double_t tZqWeight = lumi*0.07358;
   /*
   ttjWeight = 1.;
   ttWWeight = 1.;
   ttZWeight = 1.;
   tZqWeight = 1.;
*/

   // You can add an arbitrary number of signal or background trees
   dataloader->AddSignalTree    ( signalTree,     signalWeight );
   //dataloader->AddBackgroundTree( ttj, ttjWeight );
   ////dataloader->AddBackgroundTree( ttj_noneg, ttjWeight );
   dataloader->AddBackgroundTree( ttWjets, ttWWeight );
   dataloader->AddBackgroundTree( ttZ, ttZWeight );
   dataloader->AddBackgroundTree( tZq, tZqWeight );

   h_pt_l1->Scale(lumi*0.043264);//0.043264 bit for MA200_rtc04!!
   h_pt_l1_ttj->Scale(lumi*832.);//832
   h_pt_l1_ttW->Scale(lumi*0.2198);//0.2198
   h_pt_l1_ttZ->Scale(lumi*0.2432);//0.2432
   h_pt_l1_tZq->Scale(lumi*0.07358);//0.07358

   // To give different trees for training and testing, do as follows:
   //
   //dataloader->AddSignalTree( signalTrainingTree, signalTrainWeight, "Training" );
   //dataloader->AddSignalTree( signalTestTree,     signalTestWeight,  "Test" );

   // Use the following code instead of the above two or four lines to add signal and background
   // training and test events "by hand"
   // NOTE that in this case one should not give expressions (such as "var1+var2") in the input
   //      variable definition, but simply compute the expression before adding the event
   // ```cpp
   // // --- begin ----------------------------------------------------------
   // std::vector<Double_t> vars( 4 ); // vector has size of number of input variables
   // Float_t  treevars[4], weight;
   //
   // // Signal
   // for (UInt_t ivar=0; ivar<4; ivar++) signalTree->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
   // for (UInt_t i=0; i<signalTree->GetEntries(); i++) {
   //    signalTree->GetEntry(i);
   //    for (UInt_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
   //    // add training and test events; here: first half is training, second is testing
   //    // note that the weight can also be event-wise
   //    if (i < signalTree->GetEntries()/2.0) dataloader->AddSignalTrainingEvent( vars, signalWeight );
   //    else                              dataloader->AddSignalTestEvent    ( vars, signalWeight );
   // }
   //
   // // Background (has event weights)
   // background->SetBranchAddress( "weight", &weight );
   // for (UInt_t ivar=0; ivar<4; ivar++) background->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
   // for (UInt_t i=0; i<background->GetEntries(); i++) {
   //    background->GetEntry(i);
   //    for (UInt_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
   //    // add training and test events; here: first half is training, second is testing
   //    // note that the weight can also be event-wise
   //    if (i < background->GetEntries()/2) dataloader->AddBackgroundTrainingEvent( vars, backgroundWeight*weight );
   //    else                                dataloader->AddBackgroundTestEvent    ( vars, backgroundWeight*weight );
   // }
   // // --- end ------------------------------------------------------------
   // ```
   // End of tree registration

   // Set individual event weights (the variables must exist in the original TTree)
   // -  for signal    : `dataloader->SetSignalWeightExpression    ("weight1*weight2");`
   // -  for background: `dataloader->SetBackgroundWeightExpression("weight1*weight2");`
   // see for the line below: https://sourceforge.net/p/tmva/mailman/message/30782828/
   //dataloader->SetBackgroundWeightExpression( "weight" );

   // Apply additional cuts on the signal and background samples (can be different)
   TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
   TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";

   // If no numbers of events are given, half of the events in the tree are used
   // for training, and the other half for testing:
   //
   //    dataloader->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
   //
   // To also specify the number of testing events, use:
   //
   //    dataloader->PrepareTrainingAndTestTree( mycut,
   //         "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V" );
   dataloader->PrepareTrainingAndTestTree( mycuts, mycutb, "SplitMode=Random:NormMode=None:!V");
   										//"nTrain_Signal=5000:nTrain_Background=5000:SplitMode=Random:NormMode=NumEvents:!V" );
   // "nTrain_Signal=1000:nTrain_Background=10000:nTest_Signal=0:nTest_Background=0:SplitMode=Random:NormMode=None:!V");

   // ### Book MVA methods
   //
   // Please lookup the various method configuration options in the corresponding cxx files, eg:
   // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
   // it is possible to preset ranges in the option string in which the cut optimisation should be done:
   // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable

   // Cut optimisation
   if (Use["Cuts"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "Cuts",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );

   if (Use["CutsD"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsD",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate" );

   if (Use["CutsPCA"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsPCA",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA" );

   if (Use["CutsGA"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsGA",
                           "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95" );

   if (Use["CutsSA"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsSA",
                           "!H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

   // Likelihood ("naive Bayes estimator")
   if (Use["Likelihood"])
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "Likelihood",
                           "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );

   // Decorrelated likelihood
   if (Use["LikelihoodD"])
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodD",
                           "!H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate" );

   // PCA-transformed likelihood
   if (Use["LikelihoodPCA"])
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodPCA",
                           "!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=PCA" );

   // Use a kernel density estimator to approximate the PDFs
   if (Use["LikelihoodKDE"])
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodKDE",
                           "!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50" );

   // Use a variable-dependent mix of splines and kernel density estimator
   if (Use["LikelihoodMIX"])
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodMIX",
                           "!H:!V:!TransformOutput:PDFInterpolSig[0]=KDE:PDFInterpolBkg[0]=KDE:PDFInterpolSig[1]=KDE:PDFInterpolBkg[1]=KDE:PDFInterpolSig[2]=Spline2:PDFInterpolBkg[2]=Spline2:PDFInterpolSig[3]=Spline2:PDFInterpolBkg[3]=Spline2:KDEtype=Gauss:KDEiter=Nonadaptive:KDEborder=None:NAvEvtPerBin=50" );

   // Test the multi-dimensional probability density estimator
   // here are the options strings for the MinMax and RMS methods, respectively:
   //
   //      "!H:!V:VolumeRangeMode=MinMax:DeltaFrac=0.2:KernelEstimator=Gauss:GaussSigma=0.3" );
   //      "!H:!V:VolumeRangeMode=RMS:DeltaFrac=3:KernelEstimator=Gauss:GaussSigma=0.3" );
   if (Use["PDERS"])
      factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERS",
                           "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600" );

   if (Use["PDERSD"])
      factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERSD",
                           "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=Decorrelate" );

   if (Use["PDERSPCA"])
      factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERSPCA",
                           "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=PCA" );

   // Multi-dimensional likelihood estimator using self-adapting phase-space binning
   if (Use["PDEFoam"])
      factory->BookMethod( dataloader, TMVA::Types::kPDEFoam, "PDEFoam",
                           "!H:!V:SigBgSeparate=F:TailCut=0.001:VolFrac=0.0666:nActiveCells=500:nSampl=2000:nBin=5:Nmin=100:Kernel=None:Compress=T" );

   if (Use["PDEFoamBoost"])
      factory->BookMethod( dataloader, TMVA::Types::kPDEFoam, "PDEFoamBoost",
                           "!H:!V:Boost_Num=30:Boost_Transform=linear:SigBgSeparate=F:MaxDepth=4:UseYesNoCell=T:DTLogic=MisClassificationError:FillFoamWithOrigWeights=F:TailCut=0:nActiveCells=500:nBin=20:Nmin=400:Kernel=None:Compress=T" );

   // K-Nearest Neighbour classifier (KNN)
   if (Use["KNN"])
      factory->BookMethod( dataloader, TMVA::Types::kKNN, "KNN",
                           "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" );

   // H-Matrix (chi2-squared) method
   if (Use["HMatrix"])
      factory->BookMethod( dataloader, TMVA::Types::kHMatrix, "HMatrix", "!H:!V:VarTransform=None" );



   // Linear discriminant (same as Fisher discriminant)
   if (Use["LD"])
      factory->BookMethod( dataloader, TMVA::Types::kLD, "LD", "H:!V:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );



   // Fisher discriminant (same as LD)
   if (Use["Fisher"])
      factory->BookMethod( dataloader, TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );

   // Fisher with Gauss-transformed input variables
   if (Use["FisherG"])
      factory->BookMethod( dataloader, TMVA::Types::kFisher, "FisherG", "H:!V:VarTransform=Gauss" );

   // Composite classifier: ensemble (tree) of boosted Fisher classifiers
   if (Use["BoostedFisher"])
      factory->BookMethod( dataloader, TMVA::Types::kFisher, "BoostedFisher",
                           "H:!V:Boost_Num=20:Boost_Transform=log:Boost_Type=AdaBoost:Boost_AdaBoostBeta=0.2:!Boost_DetailedMonitoring" );

   // Function discrimination analysis (FDA) -- test of various fitters - the recommended one is Minuit (or GA or SA)
   if (Use["FDA_MC"])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MC",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:SampleSize=100000:Sigma=0.1" );

   if (Use["FDA_GA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_GA",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=100:Cycles=2:Steps=5:Trim=True:SaveBestGen=1" );

   if (Use["FDA_SA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_SA",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=SA:MaxCalls=15000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

   if (Use["FDA_MT"])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=2:UseImprove:UseMinos:SetBatch" );

   if (Use["FDA_GAMT"])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_GAMT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:Cycles=1:PopSize=5:Steps=5:Trim" );

   if (Use["FDA_MCMT"])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MCMT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:SampleSize=20" );

   // TMVA ANN: MLP (recommended ANN) -- all ANNs in TMVA are Multilayer Perceptrons
   if (Use["MLP"])
      factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator" );

   if (Use["MLPBFGS"])
      factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:!UseRegulator" );

   if (Use["MLPBNN"])
      factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=60:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator" ); // BFGS training with bayesian regulators



   // Multi-architecture DNN implementation.
   if (Use["DNN_CPU"] or Use["DNN_GPU"]) {
	  TString inputLayoutString = "InputLayout=1|1|24"; 
	  TString batchLayoutString= "BatchLayout=1|32|24";
	  TString layoutString ("Layout=DENSE|64|TANH,DENSE|64|TANH,DENSE|64|TANH,DENSE|64|TANH,DENSE|1|LINEAR");
	  
      // Training strategies.
	  TString training1("LearningRate=1e-3,Momentum=0.,Repetitions=1,"
	                          "ConvergenceSteps=10,BatchSize=32,TestRepetitions=1,"
	                          "MaxEpochs=30,WeightDecay=1e-4,Regularization=None,"
	                          "Optimizer=ADAM,DropConfig=0.0+0.0+0.0+0.");
           TString training2("LearningRate=1e-3,Momentum=0.9,Repetitions=1," 
			   				"ConvergenceSteps=10,BatchSize=128,TestRepetitions=1,"
							"MaxEpochs=20,WeightDecay=1e-4,Regularization=None,"
							"Optimizer=SGD,DropConfig=0.0+0.0+0.0+0.");
	  
/*	  
      TString training0("LearningRate=1e-2,Momentum=0.9,Repetitions=1,"
                        "ConvergenceSteps=30,BatchSize=256,TestRepetitions=10,"
                        "WeightDecay=1e-4,Regularization=None,"
                        "DropConfig=0.0+0.5+0.5+0.5, Multithreading=True");
      TString training1("LearningRate=1e-2,Momentum=0.9,Repetitions=1,"
                        "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
                        "WeightDecay=1e-4,Regularization=L2,"
                        "DropConfig=0.0+0.0+0.0+0.0, Multithreading=True");
      TString training2("LearningRate=1e-3,Momentum=0.0,Repetitions=1,"
                        "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
                        "WeightDecay=1e-4,Regularization=L2,"
                        "DropConfig=0.0+0.0+0.0+0.0, Multithreading=True");

      TString training3("LearningRate=1e-4,Momentum=0.0,Repetitions=1,"
                        "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
                        "WeightDecay=1e-4,Regularization=L2,"
                        "DropConfig=0.0+0.0+0.0+0.0, Multithreading=True");
      TString training4("LearningRate=1e-5,Momentum=0.0,Repetitions=1,"
                        "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
                        "WeightDecay=1e-4,Regularization=L2,"
                        "DropConfig=0.0+0.0+0.0+0.0, Multithreading=True");
*/
      TString trainingStrategyString ("TrainingStrategy=");
	  trainingStrategyString += training1 + "|" + training2;
      //trainingStrategyString += training0 + "|" + training1 + "|" + training2;
      //trainingStrategyString += training0 + "|" + training1 + "|" + training2+ "|" + training3 + "|" + training4;

      // General Options.
 //     TString dnnOptions ("!H:V:ErrorStrategy=CROSSENTROPY:VarTransform=G:"
	  //                         "WeightInitialization=XAVIER");//IgnoreEventsWithNegWeightsInTraining:True
	  TString dnnOptions ("!H:V:ErrorStrategy=CROSSENTROPY:VarTransform=G:"
		  "WeightInitialization=XAVIER");

      dnnOptions.Append (":"); dnnOptions.Append (inputLayoutString);
      dnnOptions.Append (":"); dnnOptions.Append (batchLayoutString);
      dnnOptions.Append (":"); dnnOptions.Append (layoutString);
      dnnOptions.Append (":"); dnnOptions.Append (trainingStrategyString);

	  if (Use["DNN_GPU"])
	     dnnOptions += ":Architecture=GPU";
	  else
	     dnnOptions += ":Architecture=CPU";
	  factory->BookMethod(dataloader, TMVA::Types::kDL, "DL_CPU", dnnOptions);
	  /*
      // Cuda implementation.
      if (Use["DNN_GPU"]) {
         TString gpuOptions = dnnOptions + ":Architecture=GPU";
         factory->BookMethod(dataloader, TMVA::Types::kDL, "DNN_GPU", gpuOptions);
      }
      // Multi-core CPU implementation.
      if (Use["DNN_CPU"]) {
         TString cpuOptions = dnnOptions + ":Architecture=CPU";
         factory->BookMethod(dataloader, TMVA::Types::kDL, "DNN_CPU", cpuOptions);
      }
	  */
   }

   // CF(Clermont-Ferrand)ANN
   if (Use["CFMlpANN"])
      factory->BookMethod( dataloader, TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N"  ); // n_cycles:#nodes:#nodes:...

   // Tmlp(Root)ANN
   if (Use["TMlpANN"])
      factory->BookMethod( dataloader, TMVA::Types::kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3"  ); // n_cycles:#nodes:#nodes:...

   // Support Vector Machine
   if (Use["SVM"])
      factory->BookMethod( dataloader, TMVA::Types::kSVM, "SVM", "Gamma=0.25:Tol=0.001:VarTransform=Norm" );

   cout<<"-------------> DEBUG <------------------------"<<endl;


   // Boosted Decision Trees
   if (Use["BDTG"]) // Gradient Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG",
   "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2:SkipNormalization=True:NegWeightTreatment=Pray" );
   //"!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2" );

   if (Use["BDT"])  // Adaptive Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT", "!V:NTrees=200:MinNodeSize=2.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20:NegWeightTreatment=IgnoreNegWeightsInTraining" );
   
   //SkipNormalization=True //"!H:!V:NTrees=850:MinNodeSize=5%:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );                    		
 //"!V:NTrees=200:MinNodeSize=2.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20:SkipNormalization=True:NegWeightTreatment=IgnoreNegWeightsInTraining" );//SkipNormalization=True


//                           "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );

   if (Use["BDTB"]) // Bagging
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTB",
                           "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20:NegWeightTreatment=IgnoreNegWeightsInTraining" );

   if (Use["BDTD"]) // Decorrelation + Adaptive Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTD",
                           "!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate:NegWeightTreatment=IgnoreNegWeightsInTraining" );

   if (Use["BDTF"])  // Allow Using Fisher discriminant in node splitting for (strong) linearly correlated variables
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTF",
                           "!H:!V:NTrees=500:MinNodeSize=2.5%:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20:NegWeightTreatment=IgnoreNegWeightsInTraining" );

   // RuleFit -- TMVA implementation of Friedman's method
   if (Use["RuleFit"])
      factory->BookMethod( dataloader, TMVA::Types::kRuleFit, "RuleFit",
                           "H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02" );

   // For an example of the category classifier usage, see: TMVAClassificationCategory
   //
   // --------------------------------------------------------------------------------------------------
   //  Now you can optimize the setting (configuration) of the MVAs using the set of training events
   // STILL EXPERIMENTAL and only implemented for BDT's !
   //
   //     factory->OptimizeAllMethods("SigEffAtBkg0.01","Scan");
   //     factory->OptimizeAllMethods("ROCIntegral","FitGA");
   //
   // --------------------------------------------------------------------------------------------------

   factory->TrainAllMethods();
   factory->TestAllMethods();
   factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   float integrated_lumi = 41367.;
   h_pt_l1->Scale(integrated_lumi*0.043264);//0.043264 bit for MA200_rtc04!!
   h_pt_l1_ttj->Scale(integrated_lumi*832.);//832
   h_pt_l1_ttW->Scale(integrated_lumi*0.2198);//0.2198
   h_pt_l1_ttZ->Scale(integrated_lumi*0.2432);//0.2432
   h_pt_l1_tZq->Scale(integrated_lumi*0.07358);//0.07358
   
   TCanvas *c2 = new TCanvas();
   c2->cd(); 
   h_pt_l1->Draw();
   h_pt_l1_ttj->Draw();
   h_pt_l1_ttW->Draw("sames");
   h_pt_l1_ttZ->Draw("sames");
   h_pt_l1_tZq->Draw("sames");
   
   
   
   float int_back_ttj, int_back_ttW, int_back_ttZ, int_back_tZq;
   int_back_ttj = h_pt_l1_ttj->Integral();
   int_back_ttW = h_pt_l1_ttW->Integral();
   int_back_ttZ = h_pt_l1_ttZ->Integral();
   int_back_tZq = h_pt_l1_tZq->Integral();
   cout<<"Integral of the weighted and lumi normalized signal pt(l1) histogram = "<<h_pt_l1->Integral()<<endl;
   cout<<"Integral of the weighted and lumi normalized ttj    pt(l1) histogram = "<<int_back_ttj<<endl;
   cout<<"Integral of the weighted and lumi normalized ttW    pt(l1) histogram = "<<int_back_ttW<<endl;
   cout<<"Integral of the weighted and lumi normalized ttZ    pt(l1) histogram = "<<int_back_ttZ<<endl;
   cout<<"Integral of the weighted and lumi normalized tZq    pt(l1) histogram = "<<int_back_tZq<<endl;
   cout<<"Integral of the weighted and lumi normalized total background pt(l1) histogram = "<<int_back_ttj+int_back_ttW+int_back_ttZ
	   +int_back_tZq<<endl;

   c2->Write();
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;

   auto c1 = factory->GetROCCurve(dataloader);
   c1->Draw();
   auto themethod = factory->GetMethod("dataset","BDT");
   cout<<themethod<<endl;

   delete factory;
   delete dataloader;
   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );

   return 0;
}

int main( int argc, char** argv )
{
   // Select methods (don't look at this code - not of interest)
   TString methodList;
   for (int i=1; i<argc; i++) {
      TString regMethod(argv[i]);
      if(regMethod=="-b" || regMethod=="--batch") continue;
      if (!methodList.IsNull()) methodList += TString(",");
      methodList += regMethod;
   }
   return TMVAClassification(methodList);
}

/*
Integral of the weighted and lumi normalized signal HT histogram = 55.0821
Integral of the weighted and lumi normalized ttj    HT histogram = 2246.24
Integral of the weighted and lumi normalized ttW    HT histogram = 88.7749
Integral of the weighted and lumi normalized ttZ    HT histogram = 35.2676
Integral of the weighted and lumi normalized tZq    HT histogram = 5.22717
Integral of the weighted and lumi normalized total background HT histogram = 2375.51
*/
