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

int Plots11_Efficiency()
{
gStyle->SetOptStat(0);
using namespace ROOT;

ROOT::EnableImplicitMT();

const char* Sensor1[4] = { "USTC W7P50 0E14", "IHEP W16p43 0E14", "USTC W15P49 25E14", "USTC W15P1 25E14"};
const char* Sensor2[4] = { "IHEP W10P51 0E14", "IHEP W16P52 15E14", "IHEP W16P49 25E14", "IHEP W10P49 25E14" };

int batch = 1;

int p0, pf;


std::vector<float> HV1_Vector;
std::vector<float> HV2_Vector;

std::vector<float> charge1_Vector;
std::vector<float> charge2_Vector;

std::vector<float> Error_charge1_Vector;
std::vector<float> Error_charge2_Vector;

std::vector<float> Error_HV1_Vector;
std::vector<float> Error_HV2_Vector;


if (batch == 1){
//batch 1

HV1_Vector = {107., 112., 117., 122., 127.};
Error_HV1_Vector = {0., 0., 0., 0., 0.};

HV2_Vector = {130., 135., 140., 145., 150.};
Error_HV2_Vector = {0., 0., 0., 0., 0.};

p0 = batch*100;
pf = p0 + 5;
} else if (batch ==2){ 
 //Batch2
 
HV1_Vector = {125., 128., 131., 134., 137., 140.}; //
Error_HV1_Vector = {0., 0., 0., 0., 0., 0.};

HV2_Vector = {300., 330., 360., 390., 420., 450.}; 
Error_HV2_Vector = {0., 0., 0., 0., 0., 0.};

p0 = batch*100;
pf = p0 + 6;
} else if (batch == 3){

 //Batch3

HV1_Vector = {455., 480., 505., 530., 555., 580.};
Error_HV1_Vector = {0., 0., 0., 0., 0., 0.};

HV2_Vector = {455., 480., 505., 530., 555., 580.};

p0 = batch*100;
pf = p0 + 6;
} else if(batch == 4){

//Batch4

HV1_Vector = {455., 480., 505., 530., 555., 580.};
Error_HV1_Vector = {0., 0., 0., 0., 0., 0.};

HV2_Vector = {455., 480., 505., 530., 555., 580.};
Error_HV2_Vector = {0., 0., 0., 0., 0., 0.};

p0 = batch*100;
pf = p0 + 6; 
}

const int S1i = -9000;
const int S2i = -9000;
const int S1f = -8000;
const int S2f = -8000;

for(int i = p0; i< pf; i++){
string str1 = "tree_merged_b";
string str2 = to_string(i);
string str3 = ".root";
string str4 = str1 + str2 + str3;

ROOT::RDataFrame df("tree_combined", str4);

//m = m.Define("charge_0", "charge[0]");
//m = m.Define("charge_1", "charge[1]");
auto m = df.Define("Amax_2", "Amax[2]"); 
auto m00 = m.Define("charge_2", "charge[2]");
auto n11 = m00.Define("Amax_0", "Amax[0]");
auto m000 = n11.Filter("ntrack==1 && tCFD[0] !=0 && Amax_0>70 ");


auto n = m000;


if (batch ==1){
n = m00.Filter("-0.5<LocalX && LocalX<0.5 && -0.2<LocalY && LocalY<0.2"); //Batch 1. Sensor 2
} else if (batch ==2){
n = m00.Filter("-0.4<LocalX && LocalX<0.6 && -0.15<LocalY && LocalY<0.2"); //Batch 2. Sensor 2
} else if (batch == 3){
n = m00.Filter("-0.5<LocalX && LocalX<0.5 && -0.2<LocalY && LocalY<0.2"); //Batch 3. Sensor 2
} else if (batch == 4){
n = m00.Filter("-0.5<LocalX && LocalX<0.5 && -0.2<LocalY && LocalY<0.2"); //Batch 4. Sensor 2
} 

auto h2 = n.Histo1D<float>({"Charge Sensor 2", "Charge total distribution", 100, 0, 100}, "charge_2");
//TCanvas *c2 = new TCanvas();
//c2->cd();
//h2->Draw();
//c2->SaveAs("AmaxDistribution.pdf");
TH1D *h2d = h2.GetPtr();


    // Create a new TH1F with the same binning as the TH1D
//TH1F *h2f = new TH1F("h2f", h2d->GetTitle(), h2d->GetNbinsX(), h2d->GetXaxis()->GetXmin(), h2d->GetXaxis()->GetXmax());

    // Copy bin contents and errors from TH1D to TH1F
//for (int bin = 1; bin <= h2d->GetNbinsX(); ++bin) {
  //   h2f->SetBinContent(bin, h2d->GetBinContent(bin));
  //   h2f->SetBinError(bin, h2d->GetBinError(bin));
//}

//double integral1_full = h2f->Integral();

double error1 = 0;
//double integral1_full = h2f->IntegralAndError(0,-1,error1);
double integral1_fullD = h2d->IntegralAndError(0,-1,error1);

//std::cout << "Integral TH1F " << integral1_full << " Integral TH1D "<< integral1_fullD << std::endl;

//auto charge_sensor1 = m.Take<float>("charge_1");
//auto charge_sensor2 = n.Take<float>("charge_2");

//std::vector<float>& charge_vector_sensor1 = *charge_sensor1;
//std::vector<float>& charge_vector_sensor2 = *charge_sensor2;

//auto h = m.Histo2D({"Histo2D", "Histo2D", 100, -2.5, 2.5, 100, -2.5, 2.5},"LocalX", "LocalY");

//auto n0 = n.Filter("4<charge[0]");
//auto n1 = n.Filter("4<charge[1]");
auto n2 = n.Filter("charge_2>2 && tCFD[2] != 0");

auto h3 = n2.Histo1D<float>({"Charge Sensor 2", "Charge total distribution", 100, 0, 100}, "charge_2");

TH1D *h3d = h3.GetPtr();

    // Create a new TH1F with the same binning as the TH1D
//TH1F *h3f = new TH1F("h3f", h3d->GetTitle(), h3d->GetNbinsX(), h3d->GetXaxis()->GetXmin(), h3d->GetXaxis()->GetXmax());

    // Copy bin contents and errors from TH1D to TH1F
//for (int bin = 1; bin <= h3d->GetNbinsX(); ++bin) {
//     h3f->SetBinContent(bin, h3d->GetBinContent(bin));
//     h3f->SetBinError(bin, h3d->GetBinError(bin));
//}

//double integral2_full = h3f->Integral();

//double integral2_full = h3f->IntegralAndError(0,-1,error1);
double integral2_fullD = h3d->IntegralAndError(0,-1,error1);

//std::cout << "Integral TH1F " << integral2_full << " Integral TH1D "<< integral2_fullD << std::endl;

//auto charge_condition_sensor1 = n1.Take<float>("charge_1");
//auto charge_condition_sensor2 = n2.Take<float>("charge_2");

//std::vector<float>& charge_vector_condition_sensor1 = *charge_condition_sensor1;
//std::vector<float>& charge_vector_condition_sensor2 = *charge_condition_sensor2;

float Eff = 100*integral2_fullD/integral1_fullD;

std::cout << Eff << endl;

charge2_Vector.push_back(Eff);

}

int p;
if (batch == 1){
p = 5;
} else {
p = 6;
}

TGraph *g = new TGraph(p, HV2_Vector.data(), charge2_Vector.data());
g->SetLineColor(kBlue);
g->SetMarkerColor(1);


TCanvas *c1 = new TCanvas("c1", "Canvas on which to display our histogram");
int k = 1;


//g->Draw();
//f->Draw();


TMultiGraph  *mg  = new TMultiGraph();
mg->GetXaxis()->SetLimits(0, 160); 
mg->SetMinimum(80);
mg->SetMaximum(100);  
mg->Add(g);
//mg->Add(f);
mg->Draw("AC*");



string str5 = "Batch";
string str6 = to_string(batch);
string str7 = " Not Irradiated Sensor; High Voltage [V]; Efficiency[%]";
string str8 = str5 + str6 + str7;

const char* cxs = str8.c_str();

mg->SetTitle("Batch 1. Not Irradiated Sensor; High Voltage [V]; Efficiency[%]");

auto legend = new TLegend(0.7, 0.8, 0.9, 0.9);
legend->AddEntry(g, Sensor1[batch-1], "lp");
//legend->AddEntry(f, Sensor2[batch-1], "lp");
legend->Draw();

string str9 = str5 + str6 + "_Sensors.pdf";

const char* cxx = str9.c_str();

c1->SaveAs(cxx);

return 0;
}




















