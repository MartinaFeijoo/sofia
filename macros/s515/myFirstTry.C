typedef struct EXT_STR_h101_t
{
    EXT_STR_h101_unpack_t unpack;
    EXT_STR_h101_SCI2_t s2;
    EXT_STR_h101_TPAT_t unpacktpat;
    EXT_STR_h101_MUSIC_onion_t music;
    EXT_STR_h101_AMS_onion_t ams;
    EXT_STR_h101_LOS_t los;
    EXT_STR_h101_timestamp_master_t timestamp_master;
    EXT_STR_h101_SOFAT_onion_t at;
    EXT_STR_h101_SOFSCI_onion_t sci;


} EXT_STR_h101;


void myFirstTry(const Int_t fRunId = 484, const Int_t nev = -1, const Int_t fExpId = 515)
{

  TString cRunId = Form("%04d", fRunId);
  TString cExpId = Form("%03d", fExpId);

  TStopwatch timer;

  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y%m%d_%H%M%S");

  // NumSoiSci, file names and paths -----------------------------

  TString dir = gSystem->Getenv("VMCWORKDIR");
  // TString ntuple_options = "RAW"; // For stitched data
  TString ntuple_options = "RAW,time-stitch=1000"; // For no stitched data
  TString ucesb_dir = getenv("UCESB_DIR");
  TString filename, outputFilename, upexps_dir, ucesb_path, sofiacaldir;

  if (fExpId == 515)
  {
      // Input file
      filename = "~/lmd/s515/main" + cRunId + "_0002.lmd";
      outputFilename = "output_myFirstTry/s" + cExpId + "_runId" + cRunId + "_data_offline_" + oss.str() + ".root";

      upexps_dir = ucesb_dir  + "/../upexps"; // for local computers
      ucesb_path = upexps_dir + "/202104_s515/202104_s515 --allow-errors --input-buffer=100Mi";
      ucesb_path.ReplaceAll("//", "/");
      sofiacaldir = dir + "/sofia/macros/s515/parameters/";
  }
  else
  {
      std::cout << "Experiment was not selected" << std::endl;
      gApplication->Terminate();
  }


  // store data or not ------------------------------------
  Bool_t NOTstoremappeddata = false; // if true, don't store mapped data in the root file
  Bool_t NOTstorecaldata = false;    // if true, don't store cal data in the root file
  Bool_t NOTstorehitdata = false;    // if true, don't store hit data in the root file

  // Setup: Selection of detectors ------------------------
  // --- FRS --------------------------------------------------------------------------
  Bool_t fFrsSci  = true;  // Start: Plastic scintillators at FRS
  // --- R3B standard -----------------------------------------------------------------
  Bool_t fAms     = false;   // AMS tracking detectors
  Bool_t fLos = true;      // Los scintillator for R3B experiments
  Bool_t fMusic = true;    // R3B-Music: Ionization chamber for charge-Z before GLAD

  // Create source using ucesb for input ------------------
  EXT_STR_h101 ucesb_struct;

  // Online server configuration --------------------------
  //Int_t refresh = 1; // Refresh rate for online histograms
  //Int_t port = 8888; // Port number for the online visualization, example lxgXXXX:8888

  // Create online run ------------------------------------
  R3BEventHeader* EvntHeader = new R3BEventHeader();
  FairRunOnline* run = new FairRunOnline();
  run->SetEventHeader(EvntHeader);
  run->SetRunId(fRunId);
  run->SetSink(new FairRootFileSink(outputFilename));
  //run->ActivateHttpServer(refresh, port);

  R3BUcesbSource* source =
      new R3BUcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
  source->SetMaxEvents(nev);

  // Definition of reader ---------------------------------
  R3BSci2Reader* unpacks2;
  R3BAmsReader* unpackams;
  R3BLosReader* unpacklos;
  R3BMusicReader* unpackmusic;

  // Add readers ------------------------------------------
  source->AddReader(new R3BUnpackReader(&ucesb_struct.unpack, offsetof(EXT_STR_h101, unpack)));
  source->AddReader(new R3BTrloiiTpatReader(&ucesb_struct.unpacktpat, offsetof(EXT_STR_h101, unpacktpat)));

  if (fFrsSci)
  {
    unpacks2 = new R3BSci2Reader(&ucesb_struct.s2, offsetof(EXT_STR_h101_t, s2));
    source->AddReader(unpacks2);
  }

  if (fAms)
  {
      unpackams = new R3BAmsReader((EXT_STR_h101_AMS_onion*)&ucesb_struct.ams, offsetof(EXT_STR_h101, ams));
      unpackams->SetOnline(NOTstoremappeddata);
      source->AddReader(unpackams);
  }

  if (fLos)
  {
      unpacklos = new R3BLosReader((EXT_STR_h101_LOS_t*)&ucesb_struct.los, offsetof(EXT_STR_h101, los));
      unpacklos->SetOnline(NOTstoremappeddata);
      source->AddReader(unpacklos);
  }

  if (fMusic)
  {
      unpackmusic = new R3BMusicReader((EXT_STR_h101_MUSIC_t*)&ucesb_struct.music, offsetof(EXT_STR_h101, music));
      unpackmusic->SetOnline(NOTstoremappeddata);
      source->AddReader(unpackmusic);
  }

  run->SetSource(source);

  // Runtime data base ------------------------------------
  FairRuntimeDb* rtdb = run->GetRuntimeDb();


  // Calibration files ------------------------------------
  // SOFIA parameters
  TString sofiacalfilename = "parameters/CalibParam_sofia.par";
  sofiacalfilename.ReplaceAll("//", "/");
  // Parameters for LOS
  TString loscalfilename = "parameters/tcal_los_pulser.root";
  loscalfilename.ReplaceAll("//", "/");
  // Parameters for S2 scintillator
  TString scis2calfilename = "parameters/tcal_s2.root";
  scis2calfilename.ReplaceAll("//", "/");
  //Parameters for AMS
  TString amscalfilename = "parameters/Ams_CalPar_20210427.par";
  amscalfilename.ReplaceAll("//", "/");


  // first and second are exc
  // Text file
  FairParAsciiFileIo* parIo1;
  parIo1 = new FairParAsciiFileIo();
  TList* parList1 = new TList();
  parList1->Add(new TObjString(sofiacalfilename));
  parList1->Add(new TObjString(amscalfilename));
  parIo1->open(parList1);
  rtdb->setSecondInput(parIo1);

  // Root file
  Bool_t kParameterMerged = kTRUE;
  FairParRootFileIo* parIo2 = new FairParRootFileIo(kParameterMerged);
  TList* parList2 = new TList();
  parList2->Add(new TObjString(loscalfilename));
  parList2->Add(new TObjString(scis2calfilename));
  parIo2->open(parList2);
  rtdb->setFirstInput(parIo2);

  rtdb->print();
  rtdb->addRun(fRunId);

  rtdb->getContainer("LosTCalPar");
  rtdb->setInputVersion(fRunId, (char*)"LosTCalPar", 1, 1);
  rtdb->getContainer("Sci2TCalPar");
  rtdb->setInputVersion(fRunId, (char*)"Sci2TCalPar", 1, 1);

  // Mapped -> Tcal -> Hit
  if (fMusic)
  {
      R3BMusicMapped2Cal* MusMap2Cal = new R3BMusicMapped2Cal();
      MusMap2Cal->SetOnline(NOTstorecaldata);
      run->AddTask(MusMap2Cal);

      R3BMusicCal2Hit* MusCal2Hit = new R3BMusicCal2Hit();
      MusCal2Hit->SetOnline(NOTstorehitdata);
      run->AddTask(MusCal2Hit);
  }

  if (fLos)
  {
      R3BLosMapped2Cal* losMapped2Cal = new R3BLosMapped2Cal("R3BLosMapped2Cal", 1);
      losMapped2Cal->SetNofModules(1, 8);
      losMapped2Cal->SetTrigger(1);
      losMapped2Cal->SetOnline(NOTstorecaldata);
      run->AddTask(losMapped2Cal);

      R3BLosCal2Hit* losCal2Hit = new R3BLosCal2Hit("R3BLosCal2Hit",1);
      losCal2Hit->SetLosInput(0,"./walk_param_empty.dat","./tot_param_empty.dat");
      losCal2Hit->SetTrigger(1);
      losCal2Hit->SetTpat(0);
      run->AddTask(losCal2Hit);
  }

  if (fFrsSci)
  {
      R3BSci2Mapped2Tcal* s2Mapped2Tcal = new R3BSci2Mapped2Tcal("Sci2Map2Tcal", 1);
      run->AddTask(s2Mapped2Tcal);

      R3BSci2Tcal2Hit* s2Cal2Hit = new R3BSci2Tcal2Hit("Sci2Cal2Hit",1);
      run->AddTask(s2Cal2Hit);
  }

  if (fAms)
  {
      R3BAmsMapped2StripCal* AmsMap2Cal = new R3BAmsMapped2StripCal();
      AmsMap2Cal->SetOnline(NOTstorecaldata);
      run->AddTask(AmsMap2Cal);

      R3BAmsStripCal2Hit* AmsStripCal2Hit = new R3BAmsStripCal2Hit();
      run->AddTask(AmsStripCal2Hit);
  }

  //Analysis of incoming particles (beam)
  R3BAnalysisIncomingID *AnalysisIncomingID = new R3BAnalysisIncomingID();
  run->AddTask(AnalysisIncomingID);

  // Initialize -------------------------------------------
  timer.Start();
  run->Init();
  FairLogger::GetLogger()->SetLogScreenLevel("INFO");

  // Run --------------------------------------------------
  run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);

  // Finish -----------------------------------------------
  timer.Stop();
  Double_t rtime = timer.RealTime() / 60.;
  Double_t ctime = timer.CpuTime() / 60.;
  std::cout << std::endl << std::endl;
  std::cout << "Macro finished succesfully." << std::endl;
  std::cout << "Output file is " << outputFilename << std::endl;
  std::cout << "Real time " << rtime << " min, CPU time " << ctime << " min" << std::endl << std::endl;
  gApplication->Terminate();
}
