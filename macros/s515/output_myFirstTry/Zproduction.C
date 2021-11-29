using namespace std;

void Zproduction(const Float_t nev = -1)
{
  TStopwatch timer;
  // Initialize -------------------------------------------
  timer.Start();

  // INPUT FILE
  TString filename = "s515_runId0491_data_offline_20211125_154817.root";
  cout << "Input: " << filename << endl;

  // READING FILE AND TREE
  TFile* file = TFile::Open(filename);
  TTree* tree = (TTree*)file->Get("evt");
  Bool_t fFrs = true;
  Bool_t fMusic = true;
  Bool_t fLos = true;

  // ENTRIES ----------------------------------------------
  Float_t nevents = tree->GetEntries();
  if (nev > -1)
      nevents = nev;
  cout << "Max. events: " << nevents << endl;

  auto c1 = new TCanvas("c1","c1",900,750);c1->Divide(2,2);
  auto c2 = new TCanvas("c2","c2",900,750); c2->Divide(2,2);
  auto c3 = new TCanvas("c3","c3",900,750); c3->Divide(2,2);
  TH2F* hlos[4];
  TH2F* hmusicAq[4];
  TH1F* hmusic[4];
  TCutG *cuts[4];

  for (int i=0; i<4; i++)
  {
    string htitle = "Zlos" + to_string(i+48);
    const char *htitle_char = htitle.c_str();
    string htitleAq = "ZmusicAq" + to_string(i+48);
    const char *htitleAq_char = htitleAq.c_str();
    string htitlemusic = "Zmusic" + to_string(i+48);
    const char *htitlemusic_char = htitlemusic.c_str();
    hlos[i] = new TH2F(htitle_char,htitle_char,500,2.45,2.51,500,45,53);
    hmusicAq[i] = new TH2F(htitleAq_char,htitleAq_char,500,2.45,2.51,500,45,53);
    hmusic[i] = new TH1F(htitlemusic_char,htitlemusic_char,500,42,54);
  }

  cuts[3] = new TCutG("los51",8);
  cuts[3]->SetVarX("FrsData.fAq");
  cuts[3]->SetVarY("LosHit.fZ");
  cuts[3]->SetTitle("Graph");
  cuts[3]->SetFillStyle(1000);
  // cuts[3]->SetPoint(0,2.488291,52.53441);
  // cuts[3]->SetPoint(1,2.483878,51.6023);
  // cuts[3]->SetPoint(2,2.486014,50.21428);
  // cuts[3]->SetPoint(3,2.489146,49.60638);
  // cuts[3]->SetPoint(4,2.491851,50.50809);
  // cuts[3]->SetPoint(5,2.491424,51.93664);
  // cuts[3]->SetPoint(6,2.488007,52.53441);
  // cuts[3]->SetPoint(7,2.488291,52.53441);

  // cuts[3]->SetPoint(0,2.491131,52.70285);
  // cuts[3]->SetPoint(1,2.489509,51.53609);
  // cuts[3]->SetPoint(2,2.490404,49.95754);
  // cuts[3]->SetPoint(3,2.492697,49.47711);
  // cuts[3]->SetPoint(4,2.495437,50.5615);
  // cuts[3]->SetPoint(5,2.49415,52.19497);
  // cuts[3]->SetPoint(6,2.491075,52.68912);
  // cuts[3]->SetPoint(7,2.491131,52.70285);

  cuts[3]->SetPoint(0,2.495996,52.94846);
  cuts[3]->SetPoint(1,2.493545,51.80458);
  cuts[3]->SetPoint(2,2.494901,50.23346);
  cuts[3]->SetPoint(3,2.498029,49.77867);
  cuts[3]->SetPoint(4,2.501001,50.55044);
  cuts[3]->SetPoint(5,2.500167,52.50744);
  cuts[3]->SetPoint(6,2.495996,52.96224);
  cuts[3]->SetPoint(7,2.495996,52.94846);



  cuts[2] = new TCutG("los50",8);
  cuts[2]->SetVarX("Zlos vs AoQ");
  cuts[2]->SetVarY("");
  cuts[2]->SetTitle("Graph");
  cuts[2]->SetFillStyle(1000);
  // cuts[2]->SetPoint(0,2.47549,51.58621);
  // cuts[2]->SetPoint(1,2.472817,50.44138);
  // cuts[2]->SetPoint(2,2.472984,48.48276);
  // cuts[2]->SetPoint(3,2.476993,48.23448);
  // cuts[2]->SetPoint(4,2.480167,48.74483);
  // cuts[2]->SetPoint(5,2.48,51.32414);
  // cuts[2]->SetPoint(6,2.475657,51.57241);
  // cuts[2]->SetPoint(7,2.47549,51.58621);

  // cuts[2]->SetPoint(0,2.478465,52.31329);
  // cuts[2]->SetPoint(1,2.475825,51.00178);
  // cuts[2]->SetPoint(2,2.477229,48.17385);
  // cuts[2]->SetPoint(3,2.48088,47.90745);
  // cuts[2]->SetPoint(4,2.483463,48.89108);
  // cuts[2]->SetPoint(5,2.482284,51.69852);
  // cuts[2]->SetPoint(6,2.478465,52.2928);
  // cuts[2]->SetPoint(7,2.478465,52.31329);

  cuts[2]->SetPoint(0,2.484056,52.24559);
  cuts[2]->SetPoint(1,2.479885,51.21196);
  cuts[2]->SetPoint(2,2.481606,49.31009);
  cuts[2]->SetPoint(3,2.485412,48.45562);
  cuts[2]->SetPoint(4,2.488592,49.82001);
  cuts[2]->SetPoint(5,2.487914,51.66676);
  cuts[2]->SetPoint(6,2.484108,52.23181);
  cuts[2]->SetPoint(7,2.484056,52.24559);



  cuts[1] = new TCutG("los49",8);
  cuts[1]->SetVarX("FrsData.fAq");
  cuts[1]->SetVarY("LosHit.fZ");
  cuts[1]->SetTitle("Graph");
  cuts[1]->SetFillStyle(1000);
  // cuts[1]->SetPoint(0,2.482678,51.70948);
  // cuts[1]->SetPoint(1,2.480045,49.60431);
  // cuts[1]->SetPoint(2,2.481462,46.89224);
  // cuts[1]->SetPoint(3,2.484602,45.81121);
  // cuts[1]->SetPoint(4,2.488956,47.13879);
  // cuts[1]->SetPoint(5,2.487741,49.69914);
  // cuts[1]->SetPoint(6,2.48288,51.63362);
  // cuts[1]->SetPoint(7,2.482678,51.70948);

  // cuts[1]->SetPoint(0,2.486377,51.10274);
  // cuts[1]->SetPoint(1,2.48381,49.96343);
  // cuts[1]->SetPoint(2,2.485121,46.9985);
  // cuts[1]->SetPoint(3,2.488671,46.09254);
  // cuts[1]->SetPoint(4,2.491019,47.4652);
  // cuts[1]->SetPoint(5,2.489654,50.45759);
  // cuts[1]->SetPoint(6,2.486377,51.07529);
  // cuts[1]->SetPoint(7,2.486377,51.07529);
  // cuts[1]->SetPoint(8,2.486377,51.10274);

  cuts[1]->SetPoint(0,2.491251,51.17062);
  cuts[1]->SetPoint(1,2.488279,50.12321);
  cuts[1]->SetPoint(2,2.489114,47.95948);
  cuts[1]->SetPoint(3,2.492972,46.98098);
  cuts[1]->SetPoint(4,2.497039,48.57966);
  cuts[1]->SetPoint(5,2.496361,50.21968);
  cuts[1]->SetPoint(6,2.491199,51.1844);
  cuts[1]->SetPoint(7,2.491251,51.17062);


  cuts[0] = new TCutG("los48",8);
  cuts[0]->SetVarX("FrsData.fAq");
  cuts[0]->SetVarY("LosHit.fZ");
  cuts[0]->SetTitle("Graph");
  cuts[0]->SetFillStyle(1000);
  // cuts[0]->SetPoint(0,2.469421,50.40086);
  // cuts[0]->SetPoint(1,2.467176,48.20086);
  // cuts[0]->SetPoint(2,2.468031,45.75431);
  // cuts[0]->SetPoint(3,2.471452,44.78707);
  // cuts[0]->SetPoint(4,2.474873,46.74052);
  // cuts[0]->SetPoint(5,2.473911,49.35776);
  // cuts[0]->SetPoint(6,2.46926,50.34397);
  // cuts[0]->SetPoint(7,2.469421,50.40086);

  // cuts[0]->SetPoint(0,2.47263,49.95448);
  // cuts[0]->SetPoint(1,2.470175,48.78075);
  // cuts[0]->SetPoint(2,2.47112,46.40909);
  // cuts[0]->SetPoint(3,2.474016,44.86025);
  // cuts[0]->SetPoint(4,2.478234,46.16708);
  // cuts[0]->SetPoint(5,2.476911,49.09536);
  // cuts[0]->SetPoint(6,2.472756,49.94238);
  // cuts[0]->SetPoint(7,2.47263,49.95448);

  cuts[0]->SetPoint(0,2.477956,50.10943);
  cuts[0]->SetPoint(1,2.474932,48.621);
  cuts[0]->SetPoint(2,2.475401,46.49862);
  cuts[0]->SetPoint(3,2.479729,45.80954);
  cuts[0]->SetPoint(4,2.483379,47.31174);
  cuts[0]->SetPoint(5,2.482701,49.10336);
  cuts[0]->SetPoint(6,2.478008,50.12321);
  cuts[0]->SetPoint(7,2.477956,50.10943);


  // Header Data
  R3BEventHeader* HeaderData = new R3BEventHeader();
  TBranch* brHeaderData = tree->GetBranch("EventHeader.");
  if (brHeaderData)
      brHeaderData->SetAddress(&HeaderData);
  else
      cout << "WARNING: EventHeader. was not found" << endl;

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
      FrsData->Clear();
      MusicHitData->Clear();
      LosHitData->Clear();

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

      if (frsHits > 0 && musicHits > 0 && LosHits>0)
      {
        for (int i=0; i<4;i++)
        {
          if (cuts[i]->IsInside(AoQfrs,Zlos))
          {
            hmusicAq[i]->Fill(AoQfrs,Zmusic);
            hlos[i]->Fill(AoQfrs,Zlos);
            hmusic[i]->Fill(Zmusic);
          }
        }
      }

      if (musicdata)
          delete[] musicdata;
      if (frsdata)
          delete[] frsdata;
      if(losdata)
          delete[] losdata;
  }
  // END OF LOOP IN THE EVENTS  ---------------------------

  for (int i=0; i<4;i++)
  {
    c1->cd(i+1);
    hmusicAq[i]->Draw("col");

    c2->cd(i+1);
    hlos[i]->Draw("col");

    c3->cd(i+1);
    hmusic[i]->Draw("col");
  }

  // Finish -----------------------------------------------
  timer.Stop();
  Double_t rtime = timer.RealTime() / 60.;
  Double_t ctime = timer.CpuTime() / 60.;
  cout << endl << endl;
  cout << "Macro finished succesfully." << endl;
  cout << "Real time " << rtime << " min, CPU time " << ctime << " min" << endl << endl;

}
