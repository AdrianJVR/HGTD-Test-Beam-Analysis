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

int Plots4_DeltaT_HV()
{

using namespace ROOT;

std::vector<float> Sigma_Vector1;
std::vector<float> Sigma_Vector11;
std::vector<float> Error_Sigma_Vector11;
std::vector<float> Sigma_Vector2;
std::vector<float> Sigma_Vector22;
std::vector<float> Error_Sigma_Vector22;

std::vector<float> Error_HV1_Vector;
std::vector<float> Error_HV2_Vector;

const char* Sensor1[4] = { "USTC W7P50 0E14", "IHEP W16p43 0E14", "USTC W15P49 25E14", "USTC W15P1 25E14"};
const char* Sensor2[4] = { "IHEP W10P51 0E14", "IHEP W16P52 15E14", "IHEP W16P49 25E14", "IHEP W10P49 25E14"};

int batch = 4;

int p0, pf;

std::vector<float> HV1_Vector;
std::vector<float> HV2_Vector;

if (batch == 1){
//batch 1

HV1_Vector = {107., 112., 117., 122., 127.};
Error_HV1_Vector = {0., 0., 0., 0., 0.};
Sigma_Vector11 = {33.0815, 31.3492, 29.7058, 28.3445, 29.243};
Error_Sigma_Vector11 = {0.0913248, 0.0855861, 0.0825108, 0.0834335, 0.0844844};

HV2_Vector = {130., 135., 140., 145., 150.};
Error_HV2_Vector = {0., 0., 0., 0., 0.};
Sigma_Vector22 = {30.6408, 29.3959, 28.1242, 26.815, 26.5337};
Error_Sigma_Vector22 = {0.0720362, 0.0672094, 0.0646458, 0.0655031, 0.0646707};

p0 = batch*100;
pf = p0 + 5;
} else if (batch ==2){ 
 //Batch2
 
HV1_Vector = {125., 128., 131., 134., 137., 140.};
Error_HV1_Vector = {0., 0., 0., 0., 0., 0.};
Sigma_Vector11 = {29.3144, 28.5305, 27.676, 27.7105, 30.0525, 43.5944};
Error_Sigma_Vector11 = {0.0848354, 0.0810088, 0.085567, 0.0858582, 0.0943558, 0.21496};

HV2_Vector = {300., 330., 360., 390., 420., 450.}; 
Error_HV2_Vector = {0., 0., 0., 0., 0., 0.};
Sigma_Vector22 = {40.9461, 38.1366, 35.8631, 33.5753, 31.6015, 30.0098};
Error_Sigma_Vector22 = {0.118996, 0.108766, 0.113025, 0.10857, 0.103254, 0.0968538};

p0 = batch*100;
pf = p0 + 6;
} else if (batch == 3){

 //Batch3

HV1_Vector = {455., 480., 505., 530., 555., 580.};
Error_HV1_Vector = {0., 0., 0., 0., 0., 0.};
Sigma_Vector11 = {49.7166, 47.1733, 45.5321, 43.1765, 41.5985, 40.0661};
Error_Sigma_Vector11 = {0.186773, 0.17579, 0.168643, 0.155938, 0.150914, 0.147777};

HV2_Vector = {455., 480., 505., 530., 555., 580.};
Error_HV2_Vector = {0., 0., 0., 0., 0., 0.};
Sigma_Vector22 = {50.2173, 47.3925, 45.2949, 42.7483, 41.122, 39.6058};
Error_Sigma_Vector22 = {0.123758, 0.116341, 0.110266, 0.103018, 0.0997433, 0.0962669};

p0 = batch*100;
pf = p0 + 6;
} else if(batch == 4){

//Batch4

HV1_Vector = {455., 480., 505., 530., 555., 580.};
Error_HV1_Vector = {0., 0., 0., 0., 0., 0.};
Sigma_Vector11 = {43.4921, 41.7623, 39.7966, 38.5363, 37.4011, 36.6033};
Error_Sigma_Vector11 = {0.204111, 0.192336, 0.183938, 0.182365, 0.182589, 0.182328};

HV2_Vector = {455., 480., 505., 530., 555., 580.};
Error_HV2_Vector = {0., 0., 0., 0., 0., 0.};
Sigma_Vector22 = {41.2716, 39.3021, 37.8088, 36.4033, 35.2785, 34.6893};
Error_Sigma_Vector22 = {0.134811, 0.128084, 0.125412, 0.121643, 0.119903, 0.120896};

p0 = batch*100;
pf = p0 + 6; 
}

int n;
if (batch == 1){
n = 5;
} else {
n = 6;
}

TGraph *g = new TGraphErrors(n, HV1_Vector.data(), Sigma_Vector11.data(), Error_HV1_Vector.data(), Error_Sigma_Vector11.data());
g->SetLineColor(kBlue);
//g->SetMarkerColor(4);

TGraph *f = new TGraphErrors(n, HV2_Vector.data(), Sigma_Vector22.data(), Error_HV2_Vector.data(), Error_Sigma_Vector22.data());
f->SetLineColor(kRed);

TGraphErrors *gr = new TGraphErrors();


TCanvas *c1 = new TCanvas("c1", "Canvas on which to display our histogram");
int k = 1;

//g->Draw();
//f->Draw();


TMultiGraph  *mg  = new TMultiGraph();
mg->Add(g);
mg->Add(f);
mg->Draw("AC*");

string str5 = "Batch";
string str6 = to_string(batch);
string str7 = "_Sensors; HV[V]; #sigma[ps]";
string str8 = str5 + str6 + str7;

const char* cxs = str8.c_str();

mg->SetTitle(cxs);

auto legend = new TLegend(0.7, 0.8, 0.9, 0.9);
legend->AddEntry(g, Sensor1[batch-1], "lp");
legend->AddEntry(f, Sensor2[batch-1], "lp");
legend->Draw();

string str9 = str5 + str6 + "_Sensors.pdf";

const char* cxx = str9.c_str();

c1->SaveAs(cxx);
return 0;

}
