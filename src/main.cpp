//
// Created by mateusz on 11/22/2021.
//

#include "../include/Network.h"
#include "LettersDataset.h"
#include <chrono>

#ifdef MK_WITH_ROOT
#include "TApplication.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TH1.h"
#include "TRootCanvas.h"
#include <TH2D.h>
#include <sstream>
#endif

int main(int argc, char **argv) {
#ifdef MK_WITH_ROOT
  TApplication app("app", &argc, argv);
  TCanvas canvas("canvas", "NeuralNets", 10, 10, 1600, 1000);
  TGraph error_func_graph;
  error_func_graph.SetTitle(
      "Absolute error over iterations;Iterations;Abs error");
#endif

  int sz = 10000;
  Dataset d(R"(C:\w\neural-network-library\dataset)", sz);
  Network net(100, 10, 2);
  std::vector<double> xs(sz), predictions(sz), labels(sz), err_o(sz), err_c(sz);

  for (int i = 0; i < d.Size(); i++) {
    auto iteration = d.GetTrainingIteration(i);
    const auto label_raw = iteration.label;
    const auto input_raw = iteration.input;
    auto input = input_raw.reshaped(100, 1);
    auto label = label_raw.reshaped(2, 1);

    auto out = net.FeedForward(input);
    auto err = net.Backpropagate(label, 0.01);

    if (i % 100 != 0) continue;

    err_o.push_back(abs(err(0)));
    err_c.push_back(abs(err(1)));
    predictions.push_back(out(0));
    labels.push_back(label(0));
    xs.push_back(i);
  }

#ifdef MK_WITH_ROOT
  error_func_graph.DrawGraph(xs.size(), xs.data(), err_o.data(), "color:red");
  error_func_graph.Draw();
  canvas.SaveAs("error.jpg");
  int demo_sz = 9;
  Dataset demo_data(R"(C:\w\neural-network-library\dataset)", demo_sz);

  std::vector<TH2D> imgs;
  canvas.Divide(3, 3);
  for (int i = 0; i < demo_sz; i++) {
    auto img_and_label = demo_data.GetTrainingIteration(i);
    std::string name;
    auto prediction = net.FeedForward(img_and_label.input);
    name = "C: " + std::to_string(prediction(0)) + "%, "
           + "O: " + std::to_string(prediction(1)) + "%";
    imgs.emplace_back(name.c_str(), name.c_str(), 10, 0, 10, 10, 0, 10);
    imgs.back().SetStats(0);
    imgs.back().SetFillStyle(0);
    //    imgs.back().SetContour(100);
    for (int x = 0; x < 10; x++)
      for (int y = 0; y < 10; y++)
        imgs.back().Fill(x, y, (img_and_label.input(x, y) / 2) + 0.001);
  }
  for (int i = 0; i < demo_sz; i++) {
    canvas.cd(i + 1);
    imgs[i].Draw();
  }
  canvas.SaveAs("out.jpg");
  //  canvas.Draw();
  TRootCanvas *rc = (TRootCanvas *) canvas.GetCanvasImp();
  app.Run();
#endif
  return 0;
}
