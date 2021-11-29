using namespace std;

void ZvsAoQ_LOScalibration(const Float_t nev = 1e5)
{
  TStopwatch timer;
  // Initialize -------------------------------------------
  timer.Start();

  // INPUT FILE
  TString filename = "s515_runId0497_data_offline_20211125_155551.root";
  cout << "Input: " << filename << endl;

  // READING FILE AND TREE
  TFile* file = TFile::Open(filename);
  TTree* tree = (TTree*)file->Get("evt");
  Bool_t fFrs = true;
  Bool_t fLos = true;
  Bool_t fMusic = true;
  // ENTRIES ----------------------------------------------
  Float_t nevents = tree->GetEntries();
  if (nev > -1)
      nevents = nev;
  cout << "Max. events: " << nevents << endl;

  auto c1 = new TCanvas("c1","c1",1000,950); c1->Divide(1,3);
  TH2F* h51 = new TH2F("h51","Zlos vs AoQ (Zmusic = 51)",500,2.42,2.54,500,105,130);
  TH2F* h50 = new TH2F("h50","Zlos vs AoQ (Zmusic = 50)",500,2.42,2.54,500,105,130);
  TH2F* h49 = new TH2F("h49","Zlos vs AoQ (Zmusic = 49)",500,2.42,2.54,500,105,130);
  TH2F* h48 = new TH2F("h48","Zlos vs AoQ (Zmusic = 48)",500,2.42,2.54,500,105,130);
  TH2F* h_all = new TH2F("h_all","ZlosVSAoQ (all)",500,2.42,2.54,500,105,130);

  TH1F* h51_proyec = new TH1F("h51_proyec","Zlos (Zmusic = 51)",600,105,130);
  TH1F* h50_proyec = new TH1F("h50_proyec","Zlos (Zmusic = 50)",600,105,130);
  TH1F* h49_proyec = new TH1F("h49_proyec","Zlos (Zmusic = 49)",600,105,130);
  TH1F* h48_proyec = new TH1F("h48_proyec","Zlos (Zmusic = 48)",600,105,130);

  TH2F* h51_Zs = new TH2F("h51_Zs","ZlosZmusic (Zmusic = 51)",500,45,55,500,45,55);
  TH2F* h50_Zs = new TH2F("h50_Zs","ZlosZmusic (Zmusic = 50)",500,45,55,500,45,55);
  TH2F* h49_Zs = new TH2F("h49_Zs","ZlosZmusic (Zmusic = 49)",500,45,55,500,45,55);
  TH2F* h48_Zs = new TH2F("h48_Zs","ZlosZmusic (Zmusic = 48)",500,45,55,500,45,55);


  TCutG *cut_Zmusic51 = new TCutG("musicVSlosZ51",8);
  cut_Zmusic51->SetVarX("MusicHitData.fZ");
  cut_Zmusic51->SetVarY("LosHit.fZ");
  cut_Zmusic51->SetTitle("_Zmusic51raph");
  cut_Zmusic51->SetFillStyle(1000);
  cut_Zmusic51->SetPoint(0,50.95109,132.4142);
  cut_Zmusic51->SetPoint(1,50.52838,123.1794);
  cut_Zmusic51->SetPoint(2,50.69444,114.8681);
  cut_Zmusic51->SetPoint(3,51.14734,111.0422);
  cut_Zmusic51->SetPoint(4,51.63798,119.0897);
  cut_Zmusic51->SetPoint(5,51.5776,128.4565);
  cut_Zmusic51->SetPoint(6,50.95109,132.4802);
  cut_Zmusic51->SetPoint(7,50.95109,132.4802);
  cut_Zmusic51->SetPoint(8,50.95109,132.4142);



  TCutG *cut_Zmusic50 = new TCutG("musicVSlosZ50",13); //los vs music (Zmusic = 50)
  cut_Zmusic50->SetVarX("MusicHitData.fZ");
  cut_Zmusic50->SetVarY("LosHit.fZ");
  cut_Zmusic50->SetTitle("Graph");
  cut_Zmusic50->SetFillStyle(1000);
  cut_Zmusic50->SetPoint(0,49.86966,130.5733);
  cut_Zmusic50->SetPoint(1,49.48514,121.8633);
  cut_Zmusic50->SetPoint(2,49.67414,109.7354);
  cut_Zmusic50->SetPoint(3,50.18248,107.1444);
  cut_Zmusic50->SetPoint(4,50.61913,113.5943);
  cut_Zmusic50->SetPoint(5,50.41058,127.5965);
  cut_Zmusic50->SetPoint(6,49.87617,130.4079);
  cut_Zmusic50->SetPoint(7,49.86966,130.5733);


  TCutG *cut_Zmusic49 = new TCutG("musicVSlosZ49",8);
  cut_Zmusic49->SetVarX("MusicHitData.fZ");
  cut_Zmusic49->SetVarY("LosHit.fZ");
  cut_Zmusic49->SetTitle("Graph");
  cut_Zmusic49->SetFillStyle(1000);
  cut_Zmusic49->SetPoint(0,48.85949,126.8798);
  cut_Zmusic49->SetPoint(1,48.48149,117.6736);
  cut_Zmusic49->SetPoint(2,48.67701,106.3175);
  cut_Zmusic49->SetPoint(3,49.25052,103.3958);
  cut_Zmusic49->SetPoint(4,49.65459,111.1687);
  cut_Zmusic49->SetPoint(5,49.34176,125.5017);
  cut_Zmusic49->SetPoint(6,48.83994,126.7696);
  cut_Zmusic49->SetPoint(7,48.85949,126.8798);


  TCutG *cut_Zmusic48 = new TCutG("musicVSlosZ48",8);
  cut_Zmusic48->SetVarX("MusicHitData.fZ");
  cut_Zmusic48->SetVarY("LosHit.fZ");
  cut_Zmusic48->SetTitle("Graph");
  cut_Zmusic48->SetFillStyle(1000);
  cut_Zmusic48->SetPoint(0,47.97967,122.2492);
  cut_Zmusic48->SetPoint(1,47.69291,114.8622);
  cut_Zmusic48->SetPoint(2,47.86236,105.7111);
  cut_Zmusic48->SetPoint(3,48.26642,102.8997);
  cut_Zmusic48->SetPoint(4,48.53363,109.1841);
  cut_Zmusic48->SetPoint(5,48.3316,121.3671);
  cut_Zmusic48->SetPoint(6,47.97315,122.0287);
  cut_Zmusic48->SetPoint(7,47.97967,122.2492);


  // Header Data
  R3BEventHeader* HeaderData = new R3BEventHeader();
  TBranch* brHeaderData = tree->GetBranch("EventHeader.");
  if (brHeaderData)
      brHeaderData->SetAddress(&HeaderData);
  else
      cout << "WARNING: EventHeader. was not found" << endl;

  // FRS Data
  TClonesArray* FrsData = new TClonesArray("R3BFrsData", 32);
  TBranch* branchFrsData = tree->GetBranch("FrsData");
  if (branchFrsData)
      branchFrsData->SetAddress(&FrsData);
  else
  {
      cout << "WARNING: FrsData was not found" << endl;
      fFrs = false;
  }

  // LOS Hit Data
  TClonesArray* LosHitData = new TClonesArray("R3BLosHitData", 4);
  TBranch* branchLosHitData = tree->GetBranch("LosHit");
  if (branchLosHitData)
      branchLosHitData->SetAddress(&LosHitData);
  else
  {
      cout << "WARNING: LosHit was not found" << endl;
      fLos = false;
  }

  // Music Hit Data
  TClonesArray* MusicHitData = new TClonesArray("R3BMusicHitData", 4);
  TBranch* branchMusicHitData = tree->GetBranch("MusicHitData");
  if (branchMusicHitData)
      branchMusicHitData->SetAddress(&MusicHitData);
  else
  {
      cout << "WARNING: Musichit was not found" << endl;
      fMusic = false;
  }

  // LOOP IN THE EVENTS  ----------------------------------
  for (Int_t ie = 0; ie < nevents; ie++)
  {
      // Print current event in the analysis  -------------
      printf("Processed: %d of %.0f (%.2f of 100) \r", ie + 1, nevents, 100. * (ie + 1.0) / nevents);
      fflush(stdout);

      // Clear TCloneArrays  ------------------------------
      LosHitData->Clear();
      FrsData->Clear();
      MusicHitData->Clear();

      // Get entry data  ----------------------------------
      tree->GetEntry(ie);

      // Get LOS data  -----------------------------
      Int_t LosHits = LosHitData->GetEntries();
      R3BLosHitData** losdata = new R3BLosHitData*[LosHits];
      Float_t Zlos=0.;
      if (LosHits > 0 && fLos)
      {
        int mula = 0;
        for (Int_t j = 0; j < LosHits; j++)
        {
          if (mula == 0)
          {
            losdata[j] = (R3BLosHitData*)(LosHitData->At(j));
            mula++;
          }
        }
        Zlos = losdata[0]->GetZ();
      }

      // Get MUSIC data  -------------------------------
      Int_t musicHits = MusicHitData->GetEntries();
      R3BMusicHitData** musicdata = new R3BMusicHitData*[musicHits];
      Float_t Zmusic=0.;
      if (musicHits > 0 && fMusic)
      {
        for (Int_t j = 0; j < musicHits; j++)
        {
            if( ((R3BMusicHitData*)(MusicHitData->At(j)))->GetZcharge()>40)
              {musicdata[j] = (R3BMusicHitData*)(MusicHitData->At(j));}
        }
      Zmusic = musicdata[0]->GetZcharge();
      }

      // Get FRS data  -------------------------------
      Int_t frsHits = FrsData->GetEntries();

      R3BFrsData** frsdata = new R3BFrsData*[frsHits];
      Float_t AoQfrs=0.;
      if (frsHits > 0 && fFrs)
      {
        for (Int_t j = 0; j < frsHits; j++)
          {frsdata[j] = (R3BFrsData*)(FrsData->At(j));}

      AoQfrs = frsdata[0]->GetAq();
      }

      if (frsHits > 0 && LosHits > 0 &&AoQfrs>0 &&Zlos>0)
      {
        if(cut_Zmusic51->IsInside(Zmusic,Zlos))
          {h51->Fill(AoQfrs,Zlos); h51_proyec->Fill(Zlos); h51_Zs->Fill(Zmusic,Zlos);}

        if(cut_Zmusic50->IsInside(Zmusic,Zlos))
          {h50->Fill(AoQfrs,Zlos); h50_proyec->Fill(Zlos); h50_Zs->Fill(Zmusic,Zlos);}

        if(cut_Zmusic49->IsInside(Zmusic,Zlos))
          {h49->Fill(AoQfrs,Zlos); h49_proyec->Fill(Zlos); h49_Zs->Fill(Zmusic,Zlos);}

        if(cut_Zmusic48->IsInside(Zmusic,Zlos))
          {h48->Fill(AoQfrs,Zlos); h48_proyec->Fill(Zlos); h48_Zs->Fill(Zmusic,Zlos);}

        h_all->Fill(AoQfrs,Zlos);
      }

      if (losdata)
          delete[] losdata;
      if (musicdata)
          delete[] musicdata;
      if (frsdata)
          delete[] frsdata;
  }
  // END OF LOOP IN THE EVENTS  ---------------------------

  //Drawing -------------------
  c1->cd(1);
  h50->Draw("col");
  c1->cd(2);
  h48->Draw("col");
  c1->cd(3);
  h_all->Draw("col");


  //LOS calibration
  auto c2 = new TCanvas("c2","c2",900,850); c2->Divide(2,2);
  c2->cd(1); h51_proyec->Draw();
  TFitResultPtr r51 = h51_proyec->Fit("gaus","S");
  Float_t mean51 = r51->Parameter(1);

  c2->cd(2); h50_proyec->Draw();
  TFitResultPtr r50 = h50_proyec->Fit("gaus","S");
  Float_t mean50 = r50->Parameter(1);

  c2->cd(3); h49_proyec->Draw();
  TFitResultPtr r49 = h49_proyec->Fit("gaus","S");
  Float_t mean49 = r49->Parameter(1);

  c2->cd(4); h48_proyec->Draw();
  TFitResultPtr r48 = h48_proyec->Fit("gaus","S");
  Float_t mean48 = r48->Parameter(1);

  auto c3 = new TCanvas("c3","c3",700,500);
  Float_t x[4] = {mean48,mean49,mean50,mean51}; Float_t y[4] = {48,49,50,51};
  TGraph* gr = new TGraph(4,x,y);
  gr->GetXaxis()->SetTitle("charge"); gr->GetYaxis()->SetTitle("Zlos");
  gr->Fit("pol1");
  gr->Draw("A*");


  // Finish -----------------------------------------------
  timer.Stop();
  Double_t rtime = timer.RealTime() / 60.;
  Double_t ctime = timer.CpuTime() / 60.;
  cout << endl << endl;
  cout << "Macro finished succesfully." << endl;
  cout << "Real time " << rtime << " min, CPU time " << ctime << " min" << endl << endl;

}
