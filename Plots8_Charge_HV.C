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

int Plots8_Charge_HV()
{

using namespace ROOT;

std::vector<float> Sigma_Vector1;
std::vector<float> Sigma_Vector2;

const char* Sensor1[4] = { "USTC W7P50 0E14", "IHEP W16p43 0E14", "USTC W15P49 25E14", "USTC W15P1 25E14"};
const char* Sensor2[4] = { "IHEP W10P51 0E14", "IHEP W16P52 15E14", "IHEP W16P49 25E14", "IHEP W10P49 25E14" };

int batch = 4;

int p0, pf;

std::vector<float> HV1_Vector;
std::vector<float> HV2_Vector;

std::vector<float> Charge1_Vector;
std::vector<float> Charge2_Vector;

std::vector<float> Error_Charge1_Vector;
std::vector<float> Error_Charge2_Vector;

std::vector<float> Error_HV1_Vector;
std::vector<float> Error_HV2_Vector;

if (batch == 1){
//batch 1

HV1_Vector = {107., 112., 117., 122., 127.};
Error_HV1_Vector = {0., 0., 0., 0., 0.};
Charge1_Vector = {16.927, 18.503, 20.641, 24.084, 31.006};
Error_Charge1_Vector = {0.012, 0.012, 0.014, 0.018, 0.033};

HV2_Vector = {130., 135., 140., 145., 150.};
Error_HV2_Vector = {0., 0., 0., 0., 0.};
Charge2_Vector = {17.223, 18.870, 21.140, 24.707, 31.648};
Error_Charge2_Vector = {0.011, 0.011, 0.012, 0.015, 0.026};

p0 = batch*100;
pf = p0 + 5;
} else if (batch ==2){ 
 //Batch2
 
HV1_Vector = {125., 128., 131., 134., 137., 140.}; //
Error_HV1_Vector = {0., 0., 0., 0., 0., 0.};
Charge1_Vector = {18.353, 19.984, 22.226, 26.102, 32.914, 35.};  //check this plot out
Error_Charge1_Vector = {0.013, 0.014, 0.018, 0.026, 0.040};  

HV2_Vector = {300., 330., 360., 390., 420., 450.}; 
Error_HV2_Vector = {0., 0., 0., 0., 0., 0.};
Charge2_Vector = {4.012, 4.972, 6.009, 7.497, 9.456, 11.822};
Error_Charge2_Vector = {0.006, 0.008, 0.010, 0.011, 0.014, 0.016};

p0 = batch*100;
pf = p0 + 6;
} else if (batch == 3){

 //Batch3

HV1_Vector = {455., 480., 505., 530., 555., 580.};
Error_HV1_Vector = {0., 0., 0., 0., 0., 0.};
Charge1_Vector = {2.612, 2.874, 3.240, 3.647, 4.111, 4.694};
Error_Charge1_Vector = {0.007, 0.007, 0.007, 0.007, 0.009, 0.010};

HV2_Vector = {455., 480., 505., 530., 555., 580.};
Charge2_Vector = {2.586, 2.854, 3.186, 3.606, 4.117, 4.764};
Error_Charge2_Vector = {0.005, 0.005, 0.005, 0.006, 0.006, 0.007};

p0 = batch*100;
pf = p0 + 6;
} else if(batch == 4){

//Batch4

HV1_Vector = {455., 480., 505., 530., 555., 580.};
Error_HV1_Vector = {0., 0., 0., 0., 0., 0.};
Charge1_Vector = {3.384, 3.805, 4.242, 4.797, 5.502, 6.310};
Error_Charge1_Vector = {0.010, 0.011, 0.012, 0.012, 0.014, 0.015};

HV2_Vector = {455., 480., 505., 530., 555., 580.};
Error_HV2_Vector = {0., 0., 0., 0., 0., 0.};
Charge2_Vector = {3.890, 4.477, 5.172, 6.017, 7.003, 8.247};
Error_Charge2_Vector = {0.006, 0.007, 0.008, 0.011, 0.012, 0.013};

p0 = batch*100;
pf = p0 + 6; 
}

int n;
if (batch == 1){
n = 5;
} else {
n = 6;
}

TGraph *g = new TGraphErrors(n, HV1_Vector.data(), Charge1_Vector.data(), Error_HV1_Vector.data(), Error_Charge1_Vector.data());
g->SetLineColor(kBlue);
g->SetMarkerColor(4);

TGraph *f = new TGraphErrors(n, HV2_Vector.data(), Charge2_Vector.data(), Error_HV2_Vector.data(), Error_Charge2_Vector.data());
f->SetMarkerColor(2);

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
string str7 = "_Sensors; HV[V]; Charge[fC]";
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





