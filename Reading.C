{
#include "TRandom.h"
gROOT->Reset();
char filename[14],entry[1];
   printf("%s","input filename:        ");
   scanf("%s",filename);
   printf("%s","Set entry:        ");
    scanf("%s",entry);
   Int_t ent=atoi(entry);
TFile *tfile=new TFile(filename,"Read");
TTree *tr1= (TTree*)tfile->Get("T");
TBranch *sbr=tr1->GetBranch("signal");
const Int_t m=3000;
typedef struct {
Int_t numberph;
Int_t sig0[m];
Int_t sig1[m];
Int_t sig2[m];
Int_t sig3[m];
Int_t sig4[m];
Int_t sig5[m];
Int_t sig6[m];
} Signal_st;

typedef struct {
Double_t energy_i;
Double_t energy_f;
Double_t deposit;
} Neutron_inf;

 TCanvas *c2 = new TCanvas("c2", "HpXe",0,0,681,696);
   c2->Range(500,101.956,1700,1898.04);
   c2->SetFillColor(19);
   c2->SetBorderSize(2);
   c2->SetGridx();
   c2->SetGridy();
   c2->SetLeftMargin(0.11476);
   c2->SetRightMargin(0.0866133);
   c2->SetFrameFillColor(10);

Neutron_inf neut_i;
Signal_st sig_st;

   TH1I *h0 = new TH1I("h10","proZ3",m,0,m);
   TH1I *h1 = new TH1I("h11","proZ3",m,0,m);
   TH1I *h2 = new TH1I("h12","proZ3",m,0,m);
   TH1I *h3 = new TH1I("h13","proZ3",m,0,m);
   TH1I *h4 = new TH1I("h14","proZ3",m,0,m);
   TH1I *h5 = new TH1I("h15","proZ3",m,0,m);
   TH1I *h6 = new TH1I("h16","proZ3",m,0,m);

   TH1I *h10 = new TH1I("h10","proZ3",m,0,m);
   TH1I *h11 = new TH1I("h11","proZ3",m,0,m);
   TH1I *h12 = new TH1I("h12","proZ3",m,0,m);
   TH1I *h13 = new TH1I("h13","proZ3",m,0,m);
   TH1I *h14 = new TH1I("h14","proZ3",m,0,m);
   TH1I *h15 = new TH1I("h15","proZ3",m,0,m);
   TH1I *h16 = new TH1I("h16","proZ3",m,0,m);
   h10->SetLineColor(7);
   h11->SetLineColor(8);
   h12->SetLineColor(2);
   h13->SetLineColor(3);
   h14->SetLineColor(4);
   h15->SetLineColor(13);
   h16->SetLineColor(14);
Int_t i,j,k,phe;

Double_t dep;
Int_t nu;
Int_t k=0,ent=0;
sbr->SetAddress(&sig_st);
Int_t spec[37],phot[60];

TRandom* rand=new TRandom ();


sbr->GetEntry(ent);
for( i=1;i<m;i++)
 {
  h0->SetBinContent(i,sig_st.sig0[i]);
  h1->SetBinContent(i,sig_st.sig1[i]);
  h2->SetBinContent(i,sig_st.sig2[i]);
  h3->SetBinContent(i,sig_st.sig3[i]);
  h4->SetBinContent(i,sig_st.sig4[i]);
  h5->SetBinContent(i,sig_st.sig5[i]);
  h6->SetBinContent(i,sig_st.sig6[i]);
 //if (sig_st.sig0[i]>0)
 //cout <<"rf    "<<sig_st.sig0[i]<<"   rt  "<<sig_st.sig1[i]<<endl;
 }
for (i=1;i<m;i++)
{
	spec[i]=h1->GetBinContent(i);
	printf("spec %d \n",spec[i]);
}
cout <<"ffhgfghfygh"<<endl;
for (phe=1;phe<36;phe++)
{
	if (spec[phe]>0)
	{
	for(i=0;i<spec[phe];i++)
		{
		nu=rand->Poisson(phe);
		if (nu<60)
		 {
		phot[nu]++;
		h2->Fill(nu);
		 }
		}
	}
}

//
	//h2->Fill(nu);
//tfile->Close();
//delete tfile;
//printf("popalo nepopalo %d %d\n",p,g);
}