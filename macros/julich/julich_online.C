typedef struct EXT_STR_h101_t
{
    EXT_STR_h101_unpack_t unpack;
    EXT_STR_h101_CALIFA_t califa;

} EXT_STR_h101;

void julich_online()
{

  TStopwatch timer;
  timer.Start();

  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "%Y%m%d_%H%M%S");

  const Int_t nev = -1; // Only nev events to read

  // NumSoiSci, file names and paths -----------------------------
  TString dir = gSystem->Getenv("VMCWORKDIR");
  TString ntuple_options = "RAW"; // For stitched data
  //TString ntuple_options = "RAW,time-stitch=1000"; // For no stitched data
  TString ucesb_dir = getenv("UCESB_DIR");
  TString filename, outputFilename, upexps_dir, ucesb_path;

  // filename = "~/lmd/krakow/Plastic_064_data_0013.lmd";
  // outputFilename = "krakow_Co60_" + oss.str() + ".root";

  filename = "/media/joseluis/data1/juelich_2021/data/068_2021-11-14_18-21-03/data_0001.lmd";
  outputFilename = "testJulich" + oss.str() + ".root";

  upexps_dir = ucesb_dir + "/../upexps"; // for local computers
  ucesb_path = upexps_dir + "/califaJulich21/califa --allow-errors --input-buffer=100Mi";
  ucesb_path.ReplaceAll("//", "/");

  TString califamapfilename = "Califa_CalPar.par";

  // Online server configuration --------------------------
  Int_t refresh = 1; // Refresh rate for online histograms
  Int_t port = 8888; // Port number for the online visualization, example lxgXXXX:8888
  // Create online run ------------------------------------
  R3BEventHeader* EvntHeader = new R3BEventHeader();
  FairRunOnline* run = new FairRunOnline();
  run->SetEventHeader(EvntHeader);
  //run->SetRunId(fRunId);
  run->SetSink(new FairRootFileSink(outputFilename));
  run->ActivateHttpServer(refresh, port);

  // Create source using ucesb for input ------------------
  EXT_STR_h101 ucesb_struct;

  R3BUcesbSource* source =
      new R3BUcesbSource(filename, ntuple_options, ucesb_path, &ucesb_struct, sizeof(ucesb_struct));
  source->SetMaxEvents(nev);

  Bool_t NOTstoremappeddata = false;

  source->AddReader(new R3BUnpackReader(&ucesb_struct.unpack, offsetof(EXT_STR_h101, unpack)));

  R3BCalifaJulichReader* unpackcalifa;

  unpackcalifa =
      new R3BCalifaJulichReader((EXT_STR_h101_CALIFA*)&ucesb_struct.califa, offsetof(EXT_STR_h101, califa));
  unpackcalifa->SetOnline(NOTstoremappeddata);
  source->AddReader(unpackcalifa);


  run->SetSource(source);
  // Runtime data base ------------------------------------
  FairRuntimeDb* rtdb = run->GetRuntimeDb();

  FairParAsciiFileIo* parIo1 = new FairParAsciiFileIo(); // Ascii
  parIo1->open(califamapfilename, "in");
  rtdb->setFirstInput(parIo1);
  rtdb->print();

   //tasks

   R3BCalifaMapped2CrystalCal* CalifaMap2Cal = new R3BCalifaMapped2CrystalCal();
   run->AddTask(CalifaMap2Cal);

   R3BAmsMapped2StripCal* AmsMap2Cal = new R3BAmsMapped2StripCal();
   run->AddTask(AmsMap2Cal);

   R3BAmsStripCal2Hit* AmsCal2Hit = new R3BAmsStripCal2Hit();
   AmsCal2Hit->SetJulichConfiguration();
   run->AddTask(AmsCal2Hit);


   R3BCalifaJulichOnlineSpectra* califaonline = new R3BCalifaJulichOnlineSpectra();
   run->AddTask(califaonline);

  // Initialize -------------------------------------------
  run->Init();
  FairLogger::GetLogger()->SetLogScreenLevel("INFO");


  // Run --------------------------------------------------
  run->Run((nev < 0) ? nev : 0, (nev < 0) ? 0 : nev);

  // Finish -----------------------------------------------
  timer.Stop();
  Double_t rtime = timer.RealTime();
  Double_t ctime = timer.CpuTime();
  std::cout << std::endl << std::endl;
  std::cout << "Macro finished succesfully." << std::endl;
  std::cout << "Output file is " << outputFilename << std::endl;
  std::cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << std::endl << std::endl;

}
