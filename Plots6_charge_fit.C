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

#include "Convolution.h"

int Plots6_charge_fit()
{
using namespace ROOT;

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
//Batch3

p0 = batch*100;
pf = p0 + 6;
} else if(batch == 4){
//Batch4

p0 = batch*100;
pf = p0 + 5; 
}

//int k = 1;

/*
TCanvas *c1 = new TCanvas("c1", "Canvas on which to display our histogram");
int k = 1;
for(int i = p0 +4; i< pf-1; i++){
string str1 = "tree_merged_b";
string str2 = to_string(i);
string str3 = ".root";
string str4 = str1 + str2 + str3;
string str6 = to_string(batch);
string str7 = "_fit.pdf";

ROOT::RDataFrame df("tree_combined", str4);
auto m = df.Filter("ntrack==1");
auto m00 = m.Define("charge_0", "charge[0]");
auto n0 = m00.Filter("charge[0]");

auto m0 = n0; 

string str01 = "Charge [fC] MCP Fit";
string str02 = " Batch ";
string str03 = str01 + str02 +str2;
const char* title_real = str03.c_str();

auto h0 = m0.Histo1D({"Charge MCP", title_real, 300, 0, 80}, "charge_0"); 
h0->SetLineColor(k);
k++;

auto Mean = h0->GetMean();
auto rms = h0->GetRMS();
auto Sigma = h0->GetStdDev();
 
TF1 *f_conv = new TF1("f_conv", conv, -10, 10, 6);

f_conv->SetParameters(sqrt(2)*rms, Mean, Sigma, 1.0, 1.0, 1.0);
f_conv->SetParNames("NormGauss", "MeanGauss", "SigmaGauss", "NormLandau", "MPVLandau", "EtaLandau");

TFitResultPtr fitResult = h0->Fit("f_conv", "S");

h0->DrawClone();

//legend->DrawClone("SAME");

f_conv->DrawClone("same");

string str9 = "Charge_0_Batch";
string str10 = str9 + str2 + str7;

const char* cxx = str10.c_str();

c1->SaveAs(cxx);
}

*/

//*************************************************************************************************************************************************************

/*
TCanvas *c2 = new TCanvas("c2", "Canvas on which to display our histogram");
int j = 1;
for(int i = p0 +4; i< pf-1; i++){
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

//Cuts to apply
if (batch ==1){
m1 = n1.Filter("-0.3<LocalX && LocalX<0.0 && -0.05<LocalY && LocalY<0.5 ||-0.5<LocalX && LocalX<-0.2 && 0.6<LocalY && LocalY<1.1 "); //Batch 1. Sensor 1
} else if (batch ==2){
m1 = n1.Filter("-1.1<LocalX && LocalX<-0.75 && -0.45<LocalY && LocalY< -0.2|| -0.7<LocalX && LocalX<-0.3 && -0.8<LocalY && LocalY<-0.45");//Batch 2. Sensor 1
} else if (batch == 3){
m1 = n1.Filter("0.8<LocalX && LocalX<1.2 && 1.3<LocalY && LocalY<1.6 || 0.9<LocalX && LocalX<1.3 && 0.6<LocalY && LocalY<1.2");//Batch 3. Sensor 1
} else if (batch == 4){
m1 = n1.Filter("-0.55<LocalX && LocalX<-0.25 && 0.0<LocalY && LocalY< 0.3 || -0.35<LocalX && LocalX<-0.1 && -0.4<LocalY && LocalY<0.0"); //Batch 4. Sensor 1
}
// End of the Cuts to apply


string str01 = "Charge [fC] Sensor 1 Fit";
string str02 = " Batch";
string str03 = str01 + str02 +str2;
const char* title_real = str03.c_str();

auto h1 = m1.Histo1D({"Charge Sensor 1", title_real, 300, 0, 40}, "charge_1"); 
h1->SetLineColor(j);
j++;

h1->DrawClone();

auto Mean = h1->GetMean();
auto rms = h1->GetRMS();
auto Sigma = h1->GetStdDev();
 
TF1 *f_conv = new TF1("f_conv", conv, -10, 10, 6);

f_conv->SetParameters(rms, Mean, Sigma, 8, 1.0, 1.0);
f_conv->SetParNames("NormGauss", "MeanGauss", "SigmaGauss", "NormLandau", "MPVLandau", "EtaLandau");

TFitResultPtr fitResult = h1->Fit("f_conv", "S");

h1->DrawClone();

//legend->DrawClone("SAME");

f_conv->DrawClone("same");

string str9 = "Charge_1_Batch";
string str10 = str9 + str6 + str7;

const char* cxx = str10.c_str();

c2->SaveAs(cxx);
}

*/

//*************************************************************************************************************************************************************



TCanvas *c3 = new TCanvas("c3", "Canvas on which to display our histogram");
int l = 1;
//for(int i = p0 +4; i< pf-1; i++){
string str1 = "tree_merged_b";
string str2 = "1";//to_string(i); 
string str3 = ".root";
string str4 = str1 + str2 + str3;
string str6 = "1"; //to_string(i);
string str7 = "_fit.pdf";

ROOT::RDataFrame df("tree_combined", "tree_merged_b204.root");
auto m = df.Define("charge_2", "charge[2]");
//auto m = m02.Filter("ntrack==1");
//auto n2 = m02.Filter("charge[2]");

//auto m2 = m; 


//Cuts to apply
//if (batch ==1){
//m2 = m.Filter("-0.5<LocalX && LocalX<0.5 && -0.2<LocalY && LocalY<0.2"); //Batch 1. Sensor 2
//} else if (batch ==2){
auto m2 = m.Filter("-0.4<LocalX && LocalX<0.6 && -0.15<LocalY && LocalY<0.2 && ntrack==1"); //Batch 2. Sensor 2
//} else if (batch == 3){
//m2 = m.Filter("-0.5<LocalX && LocalX<0.5 && -0.2<LocalY && LocalY<0.2"); //Batch 3. Sensor 2
//} else if (batch == 4){
//m2 = m.Filter("-0.5<LocalX && LocalX<0.5 && -0.2<LocalY && LocalY<0.2"); //Batch 4. Sensor 2
//}
// End of the Cuts to apply


string str01 = "Charge [fC] Sensor 2 Fit";
string str02 = " Batch";
string str03 = str01 + str02 +str2;
const char* title_real = str03.c_str();

auto h2 = m2.Histo1D({"Charge Sensor 2", title_real, 100, 0, 40}, "charge_2"); 
h2->SetLineColor(l);
l++;

h2->DrawClone();


auto Mean = h2->GetMean();
auto rms = h2->GetRMS();
auto Sigma = h2->GetStdDev();
 
TF1 *f_conv = new TF1("f_conv", conv, -10, 10, 6);

f_conv->SetParameters(rms, Mean, Sigma, 1.0, 1.0, 1.0);
f_conv->SetParNames("NormGauss", "MeanGauss", "SigmaGauss", "NormLandau", "MPVLandau", "EtaLandau");

TFitResultPtr fitResult = h2->Fit("f_conv", "S");

h2->DrawClone();

//legend->DrawClone("SAME");

f_conv->DrawClone("same");

string str9 = "Charge_2_Batch";
string str10 = str9 + str6 + str7;

const char* cxx = str10.c_str();

c3->SaveAs(cxx);
//}




return 0;
}





