#include "ROOT/InternalTreeUtils.hxx"
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RDataSource.hxx"
#include "ROOT/RDF/RDatasetSpec.hxx"
#include "ROOT/RDF/RInterface.hxx"
#include "ROOT/RDF/RLoopManager.hxx"
#include "ROOT/RDF/Utils.hxx"
#include <string_view>
#include "TChain.h"
#include "TDirectory.h"
#include "RtypesCore.h" // for ULong64_t
#include "TTree.h"
#include "ROOT/RVec.hxx"
#include "TLegend.h"
#include <list>
#include <iostream>
#include <vector>
#include <string>
#include <TFile.h>
#include <array>
//#include "langaus.C"
#include <TStyle.h>

#include "Convolution.h"


int Plots7_charge_Fit()
{

gStyle->SetOptStat(0);

int batch = 2;
int p0, pf;
if (batch == 1){
//batch 1
p0 = batch*100;
pf = p0 + 5;
} else if (batch ==2){ 
 //Batch2
p0 = batch*100;
pf = p0 + 6;
} else if (batch == 3){
//Batch3  Here the bining is {75, 90}
p0 = batch*100;
pf = p0 + 6;
} else if(batch == 4){
//Batch4
p0 = batch*100;
pf = p0 + 6; 
}

//Sensor 2:


int l = 1;
for(int i = p0+1; i< pf-4; i++){

TCanvas *c4 = new TCanvas("c4", "Canvas on which to display our histogram");
string str1 = "tree_merged_b";
string str2 = to_string(i); 
string str3 = ".root";
string str4 = str1 + str2 + str3;
string str6 = to_string(i);
string str7 = "_fit.pdf";

ROOT::RDataFrame df("tree_combined", str4);
auto m = df.Filter("ntrack==1");
auto m02 = m.Define("charge_2", "charge[2]");
auto n2 = m02.Filter("charge[2]");

auto m2 = n2;

//Cuts to apply
if (batch ==1){
m2 = n2.Filter("-0.5<LocalX && LocalX<0.5 && -0.2<LocalY && LocalY<0.2"); //Batch 1. Sensor 2
} else if (batch ==2){
m2 = n2.Filter("-0.3<LocalX && LocalX<0.7 && -0.17<LocalY && LocalY<0.18"); //Batch 2. Sensor 2
} else if (batch == 3){
m2 = n2.Filter("-0.5<LocalX && LocalX<0.5 && -0.2<LocalY && LocalY<0.2"); //Batch 3. Sensor 2
} else if (batch == 4){
m2 = n2.Filter("-0.52<LocalX && LocalX<0.53 && -0.2<LocalY && LocalY<0.2"); //Batch 4. Sensor 2
}
// End of the Cuts to apply

string str01 = "Charge [fC] Sensor 2 Fit";
string str02 = " Batch";
string str03 = str01 + str02 +str2;
const char* title_real = str03.c_str();

auto h2 = m2.Histo1D<float>({"Charge Sensor 2", title_real, 98, 0, 20}, "charge_2");

double fr[2];
double sv[4], pllo[4], plhi[4], fp[4], fpe[4];
fr[0]=0.3*h2->GetMean();
fr[1]=3.0*h2->GetMean();


//Batch 1:

pllo[0]=0.2; plhi[0]=5.0;
pllo[1]=1.0; plhi[1]=90.0;   
pllo[2]=0.8; plhi[2]=90000000.0;
pllo[3]=0.4; plhi[3]=8.0;

sv[0]=1.8; sv[1]=20.0; sv[2]=5000.0; sv[3]=6.0;



//pllo[0]=0.2; plhi[0]=2.0;
//pllo[1]=2.0; plhi[1]=10.0;   
//pllo[2]=0.8; plhi[2]=1000000.0;
//pllo[3]=0.4; plhi[3]=8.0;

//sv[0]=1.4; sv[1]=18.0; sv[2]=50000.0; sv[3]=3.0;


//Batch 3:

//pllo[0]=0.2; pllo[1]=4.0; pllo[2]=0.8; pllo[3]=0.4;
//plhi[0]=2.0; plhi[1]=40.0; plhi[2]=1000000.0; plhi[3]=5.0;
//sv[0]=1.4; sv[1]=18.0; sv[2]=100.0; sv[3]=3.0;

// Extract the TH1D from RResultPtr
TH1D *h2d = h2.GetPtr();

    // Create a new TH1F with the same binning as the TH1D
TH1F *h2f = new TH1F("h2f", h2d->GetTitle(), h2d->GetNbinsX(), h2d->GetXaxis()->GetXmin(), h2d->GetXaxis()->GetXmax());

    // Copy bin contents and errors from TH1D to TH1F
for (int bin = 1; bin <= h2d->GetNbinsX(); ++bin) {
     h2f->SetBinContent(bin, h2d->GetBinContent(bin));
     h2f->SetBinError(bin, h2d->GetBinError(bin));
}

//h2->GetXaxis()->SetRange(0,70);

double chisqr;
int ndf;
//TF1 *fitsnr = langaufit(h2,fr,sv,pllo,plhi,fp,fpe,&chisqr,&ndf);
TF1 *fitsnr = langaufit(h2f,fr,sv,pllo,plhi,fp,fpe,&chisqr,&ndf);
 
double SNRPeak, SNRFWHM;
langaupro(fp,SNRPeak,SNRFWHM);


//gStyle->SetOptStat(1111);
gStyle->SetOptFit(1111);
gStyle->SetLabelSize(0.03,"x");
gStyle->SetLabelSize(0.03,"y");

h2->SetLineStyle(1); 
//h2->SetLineColor(l);
h2->DrawClone();
fitsnr->DrawClone("SAME");

l++;

TPaveText *pt = new TPaveText(0.15, 0.7, 0.45, 0.9, "NDC");
pt->SetFillColor(0); // Transparent background
pt->SetTextAlign(12); // Center-align text


pt->AddText("Fit Parameters:");
pt->AddText(Form("Width = %.3f #pm %.3f", fitsnr->GetParameter(0), fitsnr->GetParError(0)));
pt->AddText(Form("MP = %.3f #pm %.3f", fitsnr->GetParameter(1), fitsnr->GetParError(1)));
pt->AddText(Form("Area = %.3f #pm %.3f", fitsnr->GetParameter(2), fitsnr->GetParError(2)));
pt->AddText(Form("GSigma = %.3f #pm %.3f", fitsnr->GetParameter(3), fitsnr->GetParError(3)));
pt->AddText(Form("#chi^{2} / NDF = %.2f / %d", fitsnr->GetChisquare(), fitsnr->GetNDF()));

pt->DrawClone("SAME"); 

//c4->Update();

string str11 = "Charge_2_Batch";
string str12 = str11 + str6 + str7;

const char* cxz = str12.c_str();

c4->SaveAs(cxz);
string s = cxz;
}



//Sensor 1:

/*
int k = 1;
for(int i = p0+1; i< pf-4; i++){


string str1 = "tree_merged_b";
string str2 = to_string(i); 
string str3 = ".root";
string str4 = str1 + str2 + str3;
string str6 = to_string(i);
string str7 = "_fit.pdf";

ROOT::RDataFrame df("tree_combined", str4);

auto m = df.Filter("ntrack==1");
auto m01 = m.Define("charge_1", "charge[1]");
auto n1 = m01.Filter("charge[1]");

auto m1 = n1;

// Cuts to apply:
if (batch ==1){
m1 = n1.Filter("-0.3<LocalX && LocalX<0.0 && -0.05<LocalY && LocalY<0.5 ||-0.5<LocalX && LocalX<-0.2 && 0.6<LocalY && LocalY<1.1 "); //Batch 1. Sensor 1
} else if (batch ==2){
m1 = n1.Filter("-1.1<LocalX && LocalX<-0.75 && -0.45<LocalY && LocalY< -0.2|| -0.7<LocalX && LocalX<-0.3 && -0.8<LocalY && LocalY<-0.45");//Batch 2. Sensor 1
} else if (batch == 3){
m1 = n1.Filter("0.8<LocalX && LocalX<1.2 && 1.3<LocalY && LocalY<1.6 || 0.9<LocalX && LocalX<1.3 && 0.6<LocalY && LocalY<1.2");//Batch 3. Sensor 1
} else if (batch == 4){
m1 = n1.Filter("-0.55<LocalX && LocalX<-0.25 && 0.0<LocalY && LocalY< 0.3 || -0.35<LocalX && LocalX<-0.1 && -0.4<LocalY && LocalY<0.0"); //Batch 4. Sensor 1
}
// End of the cuts to apply

string str01 = "Charge [fC] Sensor 1 Fit";
string str02 = " Batch";
string str03 = str01 + str02 +str2;
const char* title_real = str03.c_str();

auto h1 = m1.Histo1D<float>({"Charge Sensor 1", title_real, 146, 0, 30}, "charge_1");

double fr[2];
double sv[4], pllo[4], plhi[4], fp[4], fpe[4];
fr[0]=0.3*h1->GetMean();
fr[1]=3.0*h1->GetMean();

//Batch 400:
pllo[0]=0.4; plhi[0]=7.0;
pllo[1]=0.8; plhi[1]=50.0;   
pllo[2]=9.0; plhi[2]=5000000.0;
pllo[3]=0.4; plhi[3]=8.0;

sv[0]=1.8; sv[1]=20.0; sv[2]=50000.0; sv[3]=3.0;


//Batch 3:
//pllo[0]=0.4; pllo[1]=4.0; pllo[2]=0.8; pllo[3]=0.4;
//plhi[0]=2.0; plhi[1]=40.0; plhi[2]=1000000.0; plhi[3]=5.0;
//sv[0]=1.4; sv[1]=18.0; sv[2]=10000.0; sv[3]=3.0;



//Original:
//pllo[0]=0.5; pllo[1]=5.0; pllo[2]=1.0; pllo[3]=0.4;
//plhi[0]=7.0; plhi[1]=50.0; plhi[2]=1000000.0; plhi[3]=5.0;
//sv[0]=1.8; sv[1]=20.0; sv[2]=50000.0; sv[3]=6.0;

 

// Extract the TH1D from RResultPtr
TH1D *h1d = h1.GetPtr();

    // Create a new TH1F with the same binning as the TH1D
TH1F *h1f = new TH1F("h1f", h1d->GetTitle(), h1d->GetNbinsX(), h1d->GetXaxis()->GetXmin(), h1d->GetXaxis()->GetXmax());

    // Copy bin contents and errors from TH1D to TH1F
for (int bin = 1; bin <= h1d->GetNbinsX(); ++bin) {
     h1f->SetBinContent(bin, h1d->GetBinContent(bin));
     h1f->SetBinError(bin, h1d->GetBinError(bin));
}

//h2->GetXaxis()->SetRange(0,70);



//h1->SetLineColor(k);
double chisqr;
int ndf;
//TF1 *fitsnr = langaufit(h2,fr,sv,pllo,plhi,fp,fpe,&chisqr,&ndf);
TF1 *fitsnr = langaufit(h1f,fr,sv,pllo,plhi,fp,fpe,&chisqr,&ndf);
 
double SNRPeak, SNRFWHM;
langaupro(fp,SNRPeak,SNRFWHM);


TCanvas *c1 = new TCanvas("c1", "Canvas on which to display our histogram");

//gStyle->SetOptStat(1111);

gStyle->SetOptFit(1111);
gStyle->SetLabelSize(0.03,"x");
gStyle->SetLabelSize(0.03,"y"); 
//h1->SetLineStyle(1);  
h1->DrawClone();
fitsnr->DrawClone("SAME"); 


TPaveText *pt = new TPaveText(0.15, 0.7, 0.45, 0.9, "NDC");
pt->SetFillColor(0); // Transparent background
pt->SetTextAlign(12); // Center-align text


pt->AddText("Fit Parameters:");
pt->AddText(Form("Width = %.3f #pm %.3f", fitsnr->GetParameter(0), fitsnr->GetParError(0)));
pt->AddText(Form("MP = %.3f #pm %.3f", fitsnr->GetParameter(1), fitsnr->GetParError(1)));
pt->AddText(Form("Area = %.3f #pm %.3f", fitsnr->GetParameter(2), fitsnr->GetParError(2)));
pt->AddText(Form("GSigma = %.3f #pm %.3f", fitsnr->GetParameter(3), fitsnr->GetParError(3)));
pt->AddText(Form("#chi^{2} / NDF = %.2f / %d", fitsnr->GetChisquare(), fitsnr->GetNDF()));

pt->DrawClone("SAME");


//c1->Update();

string str11 = "Charge_1_Batch";
string str12 = str11 + str6 + str7;
k++;
const char* cxx = str12.c_str();

c1->SaveAs(cxx);
string s = cxx;
}

*/

return 0;
}


