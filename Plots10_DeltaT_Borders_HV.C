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

int Plots10_DeltaT_Borders_HV()
{

using namespace ROOT;

std::vector<float> Sigma_Vector1;
std::vector<float> Sigma_Vector2;

const char* Sensor1[4] = { "USTC W7P50 0E14", "IHEP W16p43 0E14", "USTC W15P49 25E14", "USTC W15P1 25E14"};
const char* Sensor2[4] = { "IHEP W10P51 0E14 (Borders)", "IHEP W16P52 15E14", "IHEP W16P49 25E14", "IHEP W10P49 25E14" };
const char* Sensor22[4] = { "IHEP W10P51 0E14 (Center)", "IHEP W16P52 15E14", "IHEP W16P49 25E14", "IHEP W10P49 25E14" };
const char* Sensor222[4] = { "IHEP W10P51 0E14 (Total)", "IHEP W16P52 15E14", "IHEP W16P49 25E14", "IHEP W10P49 25E14" };

int batch = 1;

int p0, pf;

std::vector<float> HV1_Vector;
std::vector<float> HV2_Vector;

std::vector<float> ΔT1_Vector;
std::vector<float> ΔT2_Vector;

std::vector<float> ΔT2_Vector_center;
std::vector<float> ΔT2_Vector_total;

std::vector<float> Error_ΔT1_Vector;
std::vector<float> Error_ΔT2_Vector;

std::vector<float> Error_ΔT2_Vector_center;
std::vector<float> Error_ΔT2_Vector_total;

std::vector<float> Error_HV1_Vector;
std::vector<float> Error_HV2_Vector;

if (batch == 1){
//batch 1

HV1_Vector = {107., 112., 117., 122., 127.};
Error_HV1_Vector = {0., 0., 0., 0., 0.};
ΔT1_Vector = {16.927, 18.503, 20.641, 24.084, 31.006};
Error_ΔT1_Vector = {0.012, 0.012, 0.014, 0.018, 0.033};

HV2_Vector = {130., 135., 140., 145., 150.};
Error_HV2_Vector = {0., 0., 0., 0., 0.};
ΔT2_Vector = {32.8205, 31.4892, 29.8917, 28.5633, 28.1182};
Error_ΔT2_Vector = {0.0673253, 0.0626447, 0.0552544, 0.055638, 0.0531734};

ΔT2_Vector_center = {30.6408, 29.3959, 28.1242, 26.815, 26.5337};
Error_ΔT2_Vector_center = {0.0720362, 0.0672094, 0.0646458, 0.0655031, 0.0646707};

ΔT2_Vector_total = {31.565, 30.2221, 28.9225, 27.6558, 27.3794};
Error_ΔT2_Vector_total = {0.0401616, 0.0376192, 0.0360824, 0.0365789, 0.036015};

//ΔT2_Vector = {29.12, 27.999, 26.7528, 25.3718, 25.0615};
//Error_ΔT2_Vector = {0.0485073, 0.0454015, 0.0426939, 0.0435652, 0.0420444};

p0 = batch*100;
pf = p0 + 5;
} else if (batch ==2){ 
 //Batch2
 
HV1_Vector = {125., 128., 131., 134., 137., 140.}; //
Error_HV1_Vector = {0., 0., 0., 0., 0., 0.};
ΔT1_Vector = {18.353, 19.984, 22.226, 26.102, 32.914, 35.};  //check this plot out
Error_ΔT1_Vector = {0.013, 0.014, 0.018, 0.026, 0.040};  

HV2_Vector = {300., 330., 360., 390., 420., 450.}; 
Error_HV2_Vector = {0., 0., 0., 0., 0., 0.};
ΔT2_Vector = {4.012, 4.972, 6.009, 7.497, 9.456, 11.822};
Error_ΔT2_Vector = {0.006, 0.008, 0.010, 0.011, 0.014, 0.016};

p0 = batch*100;
pf = p0 + 6;
} else if (batch == 3){

 //Batch3

HV1_Vector = {455., 480., 505., 530., 555., 580.};
Error_HV1_Vector = {0., 0., 0., 0., 0., 0.};
ΔT1_Vector = {2.612, 2.874, 3.240, 3.647, 4.111, 4.694};
Error_ΔT1_Vector = {0.007, 0.007, 0.007, 0.007, 0.009, 0.010};

HV2_Vector = {455., 480., 505., 530., 555., 580.};
ΔT2_Vector = {2.586, 2.854, 3.186, 3.606, 4.117, 4.764};
Error_ΔT2_Vector = {0.005, 0.005, 0.005, 0.006, 0.006, 0.007};

p0 = batch*100;
pf = p0 + 6;
} else if(batch == 4){

//Batch4

HV1_Vector = {455., 480., 505., 530., 555., 580.};
Error_HV1_Vector = {0., 0., 0., 0., 0., 0.};
ΔT1_Vector = {3.384, 3.805, 4.242, 4.797, 5.502, 6.310};
Error_ΔT1_Vector = {0.010, 0.011, 0.012, 0.012, 0.014, 0.015};

HV2_Vector = {455., 480., 505., 530., 555., 580.};
Error_HV2_Vector = {0., 0., 0., 0., 0., 0.};
ΔT2_Vector = {3.890, 4.477, 5.172, 6.017, 7.003, 8.247};
Error_ΔT2_Vector = {0.006, 0.007, 0.008, 0.011, 0.012, 0.013};

p0 = batch*100;
pf = p0 + 6; 
}

int n;
if (batch == 1){
n = 5;
} else {
n = 6;
}

//TGraph *g = new TGraphErrors(n, HV1_Vector.data(), ΔT1_Vector.data(), Error_HV1_Vector.data(), Error_ΔT1_Vector.data());
//g->SetLineColor(kBlue);
//g->SetMarkerColor(4);

TGraph *h = new TGraphErrors(n, HV2_Vector.data(), ΔT2_Vector_total.data(), Error_HV2_Vector.data(), Error_ΔT2_Vector_total.data());
h->SetLineColor(kGreen);

TGraph *g = new TGraphErrors(n, HV2_Vector.data(), ΔT2_Vector.data(), Error_HV2_Vector.data(), Error_ΔT2_Vector.data());
g->SetLineColor(kBlue);

TGraph *f = new TGraphErrors(n, HV2_Vector.data(), ΔT2_Vector_center.data(), Error_HV2_Vector.data(), Error_ΔT2_Vector_center.data());
f->SetMarkerColor(2);

TGraphErrors *gr = new TGraphErrors();


TCanvas *c1 = new TCanvas("c1", "Canvas on which to display our histogram");
int k = 1;

h->Draw();
g->Draw();
f->Draw();


TMultiGraph  *mg  = new TMultiGraph();
mg->Add(h);
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
//legend->AddEntry(g, Sensor1[batch-1], "lp");
legend->AddEntry(h, Sensor222[batch-1], "lp");
legend->AddEntry(f, Sensor22[batch-1], "lp");
legend->AddEntry(g, Sensor2[batch-1], "lp");
legend->Draw();

string str9 = str5 + str6 + "_ΔT_Sensors.pdf";

const char* cxx = str9.c_str();

c1->SaveAs(cxx);
return 0;
}
