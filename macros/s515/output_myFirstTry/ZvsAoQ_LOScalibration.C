using namespace std;

void ZvsAoQ_LOScalibration(const Float_t nev = -1)
{
  TStopwatch timer;
  // Initialize -------------------------------------------
  timer.Start();

  // INPUT FILE
  TString filename = "s515_runId0484_data_offline_20211029_161446.root";
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

  TCutG *cut_Zmusic51 = new TCutG("musicVSlosZ51",8);
  cut_Zmusic51->SetVarX("MusicHitData.fZ");
  cut_Zmusic51->SetVarY("LosHit.fZ");
  cut_Zmusic51->SetTitle("_Zmusic51raph");
  cut_Zmusic51->SetFillStyle(1000);
  cut_Zmusic51->SetPoint(0,51.00547,130.2001);
  cut_Zmusic51->SetPoint(1,50.561,126.1921);
  cut_Zmusic51->SetPoint(2,50.66137,118.997);
  cut_Zmusic51->SetPoint(3,51.27072,117.3068);
  cut_Zmusic51->SetPoint(4,51.72237,120.7837);
  cut_Zmusic51->SetPoint(5,51.46429,129.7172);
  cut_Zmusic51->SetPoint(6,51.01264,130.2001);
  cut_Zmusic51->SetPoint(7,51.00547,130.2001);

  TCutG *cut_Zmusic50 = new TCutG("musicVSlosZ50",13); //los vs music (Zmusic = 50)
  cut_Zmusic50->SetVarX("MusicHitData.fZ");
  cut_Zmusic50->SetVarY("LosHit.fZ");
  cut_Zmusic50->SetTitle("Graph");
  cut_Zmusic50->SetFillStyle(1000);
  cut_Zmusic50->SetPoint(0,49.89855,129.582);
  cut_Zmusic50->SetPoint(1,49.25091,126.5687);
  cut_Zmusic50->SetPoint(2,49.18448,123.3816);
  cut_Zmusic50->SetPoint(3,49.20939,119.8469);
  cut_Zmusic50->SetPoint(4,49.44188,115.9644);
  cut_Zmusic50->SetPoint(5,49.66606,112.6614);
  cut_Zmusic50->SetPoint(6,50.01479,112.7773);
  cut_Zmusic50->SetPoint(7,50.5462,116.37);
  cut_Zmusic50->SetPoint(8,50.49638,121.1796);
  cut_Zmusic50->SetPoint(9,50.42165,127.322);
  cut_Zmusic50->SetPoint(10,50.15595,129.3502);
  cut_Zmusic50->SetPoint(11,49.91516,129.4661);
  cut_Zmusic50->SetPoint(12,49.89855,129.582);

  TCutG *cut_Zmusic49 = new TCutG("musicVSlosZ49",8);
  cut_Zmusic49->SetVarX("MusicHitData.fZ");
  cut_Zmusic49->SetVarY("LosHit.fZ");
  cut_Zmusic49->SetTitle("Graph");
  cut_Zmusic49->SetFillStyle(1000);
  cut_Zmusic49->SetPoint(0,48.39685,124.1776);
  cut_Zmusic49->SetPoint(1,47.92407,121.0461);
  cut_Zmusic49->SetPoint(2,48.08166,111.6513);
  cut_Zmusic49->SetPoint(3,48.65294,108.7961);
  cut_Zmusic49->SetPoint(4,49.20451,113.125);
  cut_Zmusic49->SetPoint(5,49.12572,122.3355);
  cut_Zmusic49->SetPoint(6,48.41655,124.2697);
  cut_Zmusic49->SetPoint(7,48.39685,124.1776);

  TCutG *cut_Zmusic48 = new TCutG("musicVSlosZ48",8);
  cut_Zmusic48->SetVarX("MusicHitData.fZ");
  cut_Zmusic48->SetVarY("LosHit.fZ");
  cut_Zmusic48->SetTitle("Graph");
  cut_Zmusic48->SetFillStyle(1000);
  cut_Zmusic48->SetPoint(0,47.06973,123.0533);
  cut_Zmusic48->SetPoint(1,46.48905,118.176);
  cut_Zmusic48->SetPoint(2,46.79015,107.311);
  cut_Zmusic48->SetPoint(3,47.39234,105.5243);
  cut_Zmusic48->SetPoint(4,47.98019,109.5323);
  cut_Zmusic48->SetPoint(5,47.65042,122.3772);
  cut_Zmusic48->SetPoint(6,47.06973,123.0533);
  cut_Zmusic48->SetPoint(7,47.06973,123.0533);

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
      fLos = false;
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
      Float_t Zlos;
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
      Float_t Zmusic;
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
      Float_t AoQfrs;
      if (frsHits > 0 && fFrs)
      {
        for (Int_t j = 0; j < frsHits; j++)
          {frsdata[j] = (R3BFrsData*)(FrsData->At(j));}

      AoQfrs = frsdata[0]->GetAq();
      }

      if (frsHits > 0 && LosHits > 0)
      {
        if(cut_Zmusic51->IsInside(Zmusic,Zlos))
          {h51->Fill(AoQfrs,Zlos); h51_proyec->Fill(Zlos);}

        if(cut_Zmusic50->IsInside(Zmusic,Zlos))
          {h50->Fill(AoQfrs,Zlos); h50_proyec->Fill(Zlos);}

        if(cut_Zmusic49->IsInside(Zmusic,Zlos))
          {h49->Fill(AoQfrs,Zlos); h49_proyec->Fill(Zlos);}

        if(cut_Zmusic48->IsInside(Zmusic,Zlos))
          {h48->Fill(AoQfrs,Zlos); h48_proyec->Fill(Zlos);}

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
