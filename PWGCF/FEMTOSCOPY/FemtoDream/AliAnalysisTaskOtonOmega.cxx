/*
 * AliAnalysisTaskFemtoPlotration.cxx
 *
 *  Created on: 24 Nov 2017
 *      Author: bernhardhohlweger
 */

#include "AliAnalysisTaskOtonOmega.h"
#include "AliLog.h"
ClassImp(AliAnalysisTaskOtonOmega)

AliAnalysisTaskOtonOmega::AliAnalysisTaskOtonOmega()
    : AliAnalysisTaskSE(),
      fTrackBufferSize(0),
      fESDAnalysis(false),
      fCascadeTreeFlag(false),
      fOmegaTreeFlag(false),
      fMinBookingME(false),
      fMinBookingSample(false),
      fMVPileUp(false),
      fEvtCutQA(false),
      fIsMC(false),
      fAnalysis(),
      fQA(0),
      fEvtCuts(),
      fEvtHistList(0),
      fTrackCuts(),
      fTrackCutHistList(0),
      fTrackCutHistMCList(0),
      fAntiTrackCuts(),
      fAntiTrackCutHistList(0),
      fAntiTrackCutHistMCList(0),
      fv0Cuts(),
      fv0CutHistList(0),
      fv0CutHistMCList(0),
      fAntiv0Cuts(),
      fAntiv0CutHistList(0),
      fAntiv0CutHistMCList(0),
      fCascCuts(),
      fCascCutList(0),
      fCascCutMCList(0),
      fAntiCascCuts(),
      fAntiCascCutList(0),
      fAntiCascCutMCList(0),
      fCascOmegaCuts(),
      fCascOmegaCutList(0),
      fCascOmegaCutMCList(0),
      fAntiCascOmegaCuts(),
      fAntiCascOmegaCutList(0),
      fAntiCascOmegaCutMCList(0),
      fConfig(),
      fResults(0),
      fResultQA(0),
      fResultsSample(0),
      fResultQASample(0),
      fTreeCascade(0),
      fTreeOmega(0) {
}

AliAnalysisTaskOtonOmega::AliAnalysisTaskOtonOmega(const char *name,
                                                     bool isESD, bool isMC, bool CascadeTreeFlag, bool OmegaTreeFlag)
    : AliAnalysisTaskSE(name),
      fTrackBufferSize(0),
      fESDAnalysis(isESD),
      fCascadeTreeFlag(CascadeTreeFlag),
      fOmegaTreeFlag(OmegaTreeFlag),
      fMinBookingME(false),
      fMinBookingSample(false),
      fMVPileUp(false),
      fEvtCutQA(false),
      fIsMC(isMC),
      fAnalysis(),
      fQA(0),
      fEvtCuts(),
      fEvtHistList(0),
      fTrackCuts(),
      fTrackCutHistList(0),
      fTrackCutHistMCList(0),
      fAntiTrackCuts(),
      fAntiTrackCutHistList(0),
      fAntiTrackCutHistMCList(0),
      fv0Cuts(),
      fv0CutHistList(0),
      fv0CutHistMCList(0),
      fAntiv0Cuts(),
      fAntiv0CutHistList(0),
      fAntiv0CutHistMCList(0),
      fCascCuts(),
      fCascCutList(0),
      fCascCutMCList(0),
      fAntiCascCuts(),
      fAntiCascCutList(0),
      fAntiCascCutMCList(0),
      fCascOmegaCuts(),
      fCascOmegaCutList(0),
      fCascOmegaCutMCList(0),
      fAntiCascOmegaCuts(),
      fAntiCascOmegaCutList(0),
      fAntiCascOmegaCutMCList(0),
      fConfig(),
      fResults(0),
      fResultQA(0),
      fResultsSample(0),
      fResultQASample(0),
      fTreeCascade(0),
      fTreeOmega(0) {
  DefineOutput(1, TList::Class());  //Output for the Event Class and Pair Cleaner
  DefineOutput(2, TList::Class());  //Output for the Event Cuts
  DefineOutput(3, TList::Class());  //Output for the Track Cuts
  DefineOutput(4, TList::Class());  //Output for the Antitrack Cuts
  DefineOutput(5, TList::Class());  //Output for the v0 Cuts -> Moved to Omega
  DefineOutput(6, TList::Class());  //Output for the Antiv0 Cuts -> Moved to Omega
  DefineOutput(7, TList::Class());  //Output for the Cascade Cuts
  DefineOutput(8, TList::Class());  //Output for the Anti Cascade
  DefineOutput(9, TList::Class());  //Output for the Results
  DefineOutput(10, TList::Class());  //Output for the Results QA
  DefineOutput(11, TList::Class());  //Output for the Sample
  DefineOutput(12, TList::Class());  //Output for the Sample QA
  DefineOutput(13, TTree::Class());  // Cascade Tree
  DefineOutput(14, TTree::Class());  // Omega Tree
  if (fIsMC) {
    DefineOutput(15, TList::Class());  //Output for the Track Cut MC Info
    DefineOutput(16, TList::Class());  //Output for the AntiTrack Cut MC Info
    DefineOutput(17, TList::Class());  //Output for the v0 Cut MC Info
    DefineOutput(18, TList::Class());  //Output for the Antiv0 Cut MC Info
    DefineOutput(19, TList::Class());  //Output for the Xi Cut MC Info
    DefineOutput(20, TList::Class());  //Output for the AntiXi Cut MC Info
  }
}

AliAnalysisTaskOtonOmega::AliAnalysisTaskOtonOmega(
    const AliAnalysisTaskOtonOmega& task)
    : AliAnalysisTaskSE(task),
      fTrackBufferSize(task.fTrackBufferSize),
      fESDAnalysis(task.fESDAnalysis),
      fCascadeTreeFlag(task.fCascadeTreeFlag),
      fOmegaTreeFlag(task.fOmegaTreeFlag),
      fMinBookingME(task.fMinBookingME),
      fMinBookingSample(task.fMinBookingSample),
      fMVPileUp(task.fMVPileUp),
      fEvtCutQA(task.fEvtCutQA),
      fIsMC(task.fIsMC),
      fAnalysis(task.fAnalysis),
      fQA(task.fQA),
      fEvtCuts(task.fEvtCuts),
      fEvtHistList(task.fEvtHistList),
      fTrackCuts(task.fTrackCuts),
      fTrackCutHistList(task.fTrackCutHistList),
      fTrackCutHistMCList(task.fTrackCutHistMCList),
      fAntiTrackCuts(task.fAntiTrackCuts),
      fAntiTrackCutHistList(task.fAntiTrackCutHistList),
      fAntiTrackCutHistMCList(task.fAntiTrackCutHistMCList),
      fv0Cuts(task.fv0Cuts),
      fv0CutHistList(task.fv0CutHistList),
      fv0CutHistMCList(task.fv0CutHistMCList),
      fAntiv0Cuts(task.fAntiv0Cuts),
      fAntiv0CutHistList(task.fAntiv0CutHistList),
      fAntiv0CutHistMCList(task.fAntiv0CutHistMCList),
      fCascCuts(task.fCascCuts),
      fCascCutList(task.fCascCutList),
      fCascCutMCList(task.fCascCutMCList),
      fAntiCascCuts(task.fAntiCascCuts),
      fAntiCascCutList(task.fAntiCascCutList),
      fAntiCascCutMCList(task.fAntiCascCutMCList),
      fCascOmegaCuts(task.fCascOmegaCuts),
      fCascOmegaCutList(task.fCascOmegaCutList),
      fCascOmegaCutMCList(task.fCascOmegaCutMCList),
      fAntiCascOmegaCuts(task.fAntiCascOmegaCuts),
      fAntiCascOmegaCutList(task.fAntiCascOmegaCutList),
      fAntiCascOmegaCutMCList(task.fAntiCascOmegaCutMCList),
      fConfig(task.fConfig),
      fResults(task.fResults),
      fResultQA(task.fResultQA),
      fResultsSample(task.fResultsSample),
      fResultQASample(task.fResultQASample),
      fTreeCascade(task.fTreeCascade),
      fTreeOmega(task.fTreeOmega) {
}

AliAnalysisTaskOtonOmega& AliAnalysisTaskOtonOmega::operator=(
    const AliAnalysisTaskOtonOmega& task) {
  if (this != &task) {
    AliAnalysisTaskSE::operator=(task);
    this->fTrackBufferSize = task.fTrackBufferSize;
    this->fESDAnalysis = task.fESDAnalysis;
    this->fMinBookingME = task.fMinBookingME;
    this->fMinBookingSample = task.fMinBookingSample;
    this->fMVPileUp = task.fMVPileUp;
    this->fEvtCutQA = task.fEvtCutQA;
    this->fIsMC = task.fIsMC;
    this->fAnalysis = task.fAnalysis;
    this->fQA = task.fQA;
    this->fEvtCuts = task.fEvtCuts;
    this->fEvtHistList = task.fEvtHistList;
    this->fTrackCuts = task.fTrackCuts;
    this->fTrackCutHistList = task.fTrackCutHistList;
    this->fTrackCutHistMCList = task.fTrackCutHistMCList;
    this->fAntiTrackCuts = task.fAntiTrackCuts;
    this->fAntiTrackCutHistList = task.fAntiTrackCutHistList;
    this->fAntiTrackCutHistMCList = task.fAntiTrackCutHistMCList;
    this->fv0Cuts = task.fv0Cuts;
    this->fv0CutHistList = task.fv0CutHistList;
    this->fv0CutHistMCList = task.fv0CutHistMCList;
    this->fAntiv0Cuts = task.fAntiv0Cuts;
    this->fAntiv0CutHistList = task.fAntiv0CutHistList;
    this->fAntiv0CutHistMCList = task.fAntiv0CutHistMCList;
    this->fCascCuts = task.fCascCuts;
    this->fCascCutList = task.fCascCutList;
    this->fCascCutMCList = task.fCascCutMCList;
    this->fAntiCascCuts = task.fAntiCascCuts;
    this->fAntiCascCutList = task.fAntiCascCutList;
    this->fAntiCascCutMCList = task.fAntiCascCutMCList;
    this->fCascOmegaCuts = task.fCascOmegaCuts;
    this->fCascOmegaCutList = task.fCascOmegaCutList;
    this->fCascOmegaCutMCList = task.fCascOmegaCutMCList;
    this->fAntiCascOmegaCuts = task.fAntiCascOmegaCuts;
    this->fAntiCascOmegaCutList = task.fAntiCascOmegaCutList;
    this->fAntiCascOmegaCutMCList = task.fAntiCascOmegaCutMCList;
    this->fConfig = task.fConfig;
    this->fResults = task.fResults;
    this->fResultQA = task.fResultQA;
    this->fResultsSample = task.fResultsSample;
    this->fResultQASample = task.fResultQASample;
  }
  return *this;
}

AliAnalysisTaskOtonOmega::~AliAnalysisTaskOtonOmega() {
  if (fAnalysis) {
    delete fAnalysis;
  }
}

void AliAnalysisTaskOtonOmega::UserCreateOutputObjects() {
  fAnalysis = new AliOtonOmegaAnalysis();
  fAnalysis->SetTrackBufferSize(fTrackBufferSize);
  fAnalysis->SetMVPileUp(fMVPileUp);
  fAnalysis->SetEvtCutQA(fEvtCutQA);

  if (fEvtCuts) {
    fAnalysis->SetEventCuts(fEvtCuts);
  } else {
    AliFatal("Event cuts missing!");
  }
  if (fTrackCuts) {
    fAnalysis->SetTrackCuts(fTrackCuts);
  } else {
    AliFatal("TrackCuts missing!");
  }
  if (fAntiTrackCuts) {
    fAnalysis->SetAntiTrackCuts(fAntiTrackCuts);
  } else {
    AliFatal("Antitrack cuts missing");
  }
//Leave v0's apart
/*
  if (fv0Cuts) {
    fAnalysis->Setv0Cuts(fv0Cuts);
  } else {
    AliFatal("v0 cuts missing");
  }
  if (fAntiv0Cuts) {
    fAnalysis->SetAntiv0Cuts(fAntiv0Cuts);
  } else {
    AliFatal("Antiv0 cuts missing");
  }
*/
  if (fCascCuts) {
    fAnalysis->SetCascadeCuts(fCascCuts);
  } else {
    AliFatal("Cascade cuts missing");
  }
  if (fAntiCascCuts) {
    fAnalysis->SetAntiCascadeCuts(fAntiCascCuts);
  } else {
    AliFatal("AntiCascade cuts missing");
  }
  if (fCascOmegaCuts) {
    fAnalysis->SetCascadeOmegaCuts(fCascOmegaCuts);
  } else {
    AliFatal("Cascade cuts missing");
  }
  if (fAntiCascOmegaCuts) {
    fAnalysis->SetAntiCascadeOmegaCuts(fAntiCascOmegaCuts);
  } else {
    AliFatal("AntiCascade cuts missing");
  }

  if (fConfig) {
    fAnalysis->SetCollectionConfig(fConfig);
    fMinBookingME = fConfig->GetMinimalBookingME();
    fMinBookingSample = fConfig->GetMinimalBookingSample();
  } else {
    AliFatal("Event Collection Config missing");
  }

  fAnalysis->Init(fIsMC, GetCollisionCandidates());
  if ((!fMinBookingME) || (!fMinBookingSample)) {
    if (fAnalysis->GetQAList()) {
      fQA = fAnalysis->GetQAList();
    } else {
      fQA = new TList();
      fQA->SetName("QA");
      fQA->SetOwner();
    }
  } else {
    fQA = new TList();
    fQA->SetName("QA");
    fQA->SetOwner();
  }

  if (!fMinBookingME) {
    if (fAnalysis->GetResultQAList()) {
      fResultQA = fAnalysis->GetResultQAList();
    } else {
      fResultQA = new TList();
      fResultQA->SetName("ResultQA");
      fResultQA->SetOwner();
    }
  } else {
    fResultQA = new TList();
    fResultQA->SetName("ResultQA");
    fResultQA->SetOwner();
  }

  if (!fMinBookingSample) {
    if (fAnalysis->GetResultSampleQAList()) {
      fResultQASample = fAnalysis->GetResultSampleQAList();
    } else {
      fResultQASample = new TList();
      fResultQASample->SetOwner();
      fResultQASample->SetName("ResultsQASample");
    }
  } else {
    fResultQASample = new TList();
    fResultQASample->SetOwner();
    fResultQASample->SetName("ResultsQASample");
  }

  if (!fEvtCuts->GetMinimalBooking()) {
    if (fAnalysis->GetEventCutHists()) {
      fEvtHistList = fAnalysis->GetEventCutHists();
    }
  } else {
    fEvtHistList = new TList();
    fEvtHistList->SetName("EventCuts");
    fEvtHistList->SetOwner();
  }
  if (fAnalysis->GetTrackCutHists()) {
    fTrackCutHistList = fAnalysis->GetTrackCutHists();
  } else {
    fTrackCutHistList = new TList();
    fTrackCutHistList->SetName("TrackCuts");
    fTrackCutHistList->SetOwner();
  }
  if (fAnalysis->GetAntitrackCutHists()) {
    fAntiTrackCutHistList = fAnalysis->GetAntitrackCutHists();
  } else {
    fAntiTrackCutHistList = new TList();
    fAntiTrackCutHistList->SetName("AntiTrackCuts");
    fAntiTrackCutHistList->SetOwner();
  }

//Leave v0s apart
/*
  if (fAnalysis->Getv0CutHist()) {
    fv0CutHistList = fAnalysis->Getv0CutHist();
  } else {
    fv0CutHistList = new TList();
    fv0CutHistList->SetName("v0Cuts");
    fv0CutHistList->SetOwner();
  }
  if (fAnalysis->GetAntiv0CutHist()) {
    fAntiv0CutHistList = fAnalysis->GetAntiv0CutHist();
  } else {
    fAntiv0CutHistList = new TList();
    fAntiv0CutHistList->SetName("Antiv0Cuts");
    fAntiv0CutHistList->SetOwner();
  }
*/

  if (fAnalysis->GetCascadeCutHist()) {
    fCascCutList = fAnalysis->GetCascadeCutHist();
  } else {
    fCascCutList = new TList();
    fCascCutList->SetName("CascadeCuts");
    fCascCutList->SetOwner();
  }
  if (fAnalysis->GetAntiCascadeCutHist()) {
    fAntiCascCutList = fAnalysis->GetAntiCascadeCutHist();
  } else {
    fAntiCascCutList = new TList();
    fAntiCascCutList->SetName("AntiCascadeCuts");
    fAntiCascCutList->SetOwner();
  }

  if (fAnalysis->GetCascadeOmegaCutHist()) {
    fCascOmegaCutList = fAnalysis->GetCascadeOmegaCutHist();
  } else {
    fCascOmegaCutList = new TList();
    fCascOmegaCutList->SetName("CascadeOmegaCuts");
    fCascOmegaCutList->SetOwner();
  }
  if (fAnalysis->GetAntiCascadeOmegaCutHist()) {
    fAntiCascOmegaCutList = fAnalysis->GetAntiCascadeOmegaCutHist();
  } else {
    fAntiCascOmegaCutList = new TList();
    fAntiCascOmegaCutList->SetName("AntiCascadeOmegaCuts");
    fAntiCascOmegaCutList->SetOwner();
  }

  //Results we always post
  if (fAnalysis->GetResultList()) {
    fResults = fAnalysis->GetResultList();
  } else {
    AliWarning("Results List not Available");
    fResults = new TList();
    fResults->SetOwner();
    fResults->SetName("ResultsSample");
  }
  if (fAnalysis->GetResultSampleList()) {
    fResultsSample = fAnalysis->GetResultSampleList();
  } else {
    AliWarning("Results Sample List not Available");
    fResultsSample = new TList();
    fResultsSample->SetOwner();
    fResultsSample->SetName("ResultsSample");
  }
  if(fAnalysis->GetTreeCascade()){
   fTreeCascade = fAnalysis->GetTreeCascade();
  }else{
   AliFatal(" fTreeCascade missing ");
  }
  if(fAnalysis->GetTreeOmega()){
   fTreeOmega = fAnalysis->GetTreeOmega();
  }else{
   AliFatal(" fTreeOmega missing ");
  }

  PostData(1, fQA);
  PostData(2, fEvtHistList);
  PostData(3, fTrackCutHistList);
  PostData(4, fAntiTrackCutHistList);
//  PostData(5, fv0CutHistList);// ->moved to omega
//  PostData(6, fAntiv0CutHistList);//  -> moved to omega
  PostData(5, fCascOmegaCutList);
  PostData(6, fAntiCascOmegaCutList);
  PostData(7, fCascCutList);
  PostData(8, fAntiCascCutList);
  PostData(9, fResults);
  PostData(10, fResultQA);
  PostData(11, fResultsSample);
  PostData(12, fResultQASample);
  PostData(13, fTreeCascade);
  PostData(14, fTreeOmega);

  if (fIsMC) {
    if (!fTrackCuts->GetMinimalBooking()) {
      if (fTrackCuts->GetIsMonteCarlo()) {
        fTrackCutHistMCList = fTrackCuts->GetMCQAHists();
      }
    } else {
      fTrackCutHistMCList = new TList();
      fTrackCutHistMCList->SetName("MCTrkCuts");
      fTrackCutHistMCList->SetOwner();
    }
    if (!fAntiTrackCuts->GetMinimalBooking()) {
      if (fAntiTrackCuts->GetIsMonteCarlo()) {
        fAntiTrackCutHistMCList = fAntiTrackCuts->GetMCQAHists();
      }
    } else {
      fAntiTrackCutHistMCList = new TList();
      fAntiTrackCutHistMCList->SetName("MCAntiTrkCuts");
      fAntiTrackCutHistMCList->SetOwner();
    }

//Leave v0s apart
/*
    if (!fv0Cuts->GetMinimalBooking()) {
      if (fv0Cuts->GetIsMonteCarlo()) {
        fv0CutHistMCList = fv0Cuts->GetMCQAHists();
      }
    } else {
      fv0CutHistMCList = new TList();
      fv0CutHistMCList->SetName("MCv0Cuts");
      fv0CutHistMCList->SetOwner();
    }
    if (!fAntiv0Cuts->GetMinimalBooking()) {
      if (fAntiv0Cuts->GetIsMonteCarlo()) {
        fAntiv0CutHistMCList = fAntiv0Cuts->GetMCQAHists();
      }
    } else {
      fAntiv0CutHistMCList = new TList();
      fAntiv0CutHistMCList->SetName("MCAntiv0Cuts");
      fAntiv0CutHistMCList->SetOwner();
    }
*/


    if (!fCascCuts->GetMinimalBooking()) {
      if (fCascCuts->GetIsMonteCarlo()) {
        fCascCutMCList = fCascCuts->GetMCQAHists();
      }
    } else {
      fCascCutMCList = new TList();
      fCascCutMCList->SetName("MCCascCuts");
      fCascCutMCList->SetOwner();
    }
    if (!fAntiCascCuts->GetMinimalBooking()) {
      if (fAntiCascCuts->GetIsMonteCarlo()) {
        fAntiCascCutMCList = fAntiCascCuts->GetMCQAHists();
      }
    } else {
      fAntiCascCutMCList = new TList();
      fAntiCascCutMCList->SetName("MCAntiCascCuts");
      fAntiCascCutMCList->SetOwner();
    }


    if (!fCascOmegaCuts->GetMinimalBooking()) {
      if (fCascOmegaCuts->GetIsMonteCarlo()) {
        fCascOmegaCutMCList = fCascOmegaCuts->GetMCQAHists();
      }
    } else {
      fCascOmegaCutMCList = new TList();
      fCascOmegaCutMCList->SetName("MCCascOmegaCuts");
      fCascOmegaCutMCList->SetOwner();
    }
    if (!fAntiCascOmegaCuts->GetMinimalBooking()) {
      if (fAntiCascOmegaCuts->GetIsMonteCarlo()) {
        fAntiCascOmegaCutMCList = fAntiCascOmegaCuts->GetMCQAHists();
      }
    } else {
      fAntiCascOmegaCutMCList = new TList();
      fAntiCascOmegaCutMCList->SetName("MCAntiCascOmegaCuts");
      fAntiCascOmegaCutMCList->SetOwner();
    }


    PostData(15, fTrackCutHistMCList);
    PostData(16, fAntiTrackCutHistMCList);
//move v0
//    PostData(17, fv0CutHistMCList);
//    PostData(18, fAntiv0CutHistMCList);
    PostData(17, fCascOmegaCutMCList);
    PostData(18, fAntiCascOmegaCutMCList);
    PostData(19, fCascCutMCList);
    PostData(20, fAntiCascCutMCList);
  }
}

void AliAnalysisTaskOtonOmega::UserExec(Option_t *) {
  if (fESDAnalysis) {
    AliESDEvent *Event = static_cast<AliESDEvent*>(fInputEvent);
    AliMCEvent *mcEvent=nullptr;
    if (fIsMC) {
      mcEvent = MCEvent();
    }
    if (!Event) {
      AliWarning("No Input Event");
    } else {
      fAnalysis->Make(Event, mcEvent, fCascadeTreeFlag, fOmegaTreeFlag);
    }
  } else {
    AliAODEvent *Event = static_cast<AliAODEvent*>(fInputEvent);
    if (!Event) {
      AliWarning("No Input Event");
    } else {
      fAnalysis->Make(Event, fOmegaTreeFlag);
    }
  }
  PostData(1, fQA);
  PostData(2, fEvtHistList);
  PostData(3, fTrackCutHistList);
  PostData(4, fAntiTrackCutHistList);
//  PostData(5, fv0CutHistList);
//  PostData(6, fAntiv0CutHistList);
  PostData(5, fCascOmegaCutList);
  PostData(6, fAntiCascOmegaCutList);
  PostData(7, fCascCutList);
  PostData(8, fAntiCascCutList);
  PostData(9, fResults);
  PostData(10, fResultQA);
  PostData(11, fResultsSample);
  PostData(12, fResultQASample);
  PostData(13, fTreeCascade);
  PostData(14, fTreeOmega);
  if (fIsMC) {
    PostData(15, fTrackCutHistMCList);
    PostData(16, fAntiTrackCutHistMCList);
//    PostData(17, fv0CutHistMCList);
//    PostData(18, fAntiv0CutHistMCList);
    PostData(17, fCascOmegaCutMCList);
    PostData(18, fAntiCascOmegaCutMCList);
    PostData(19, fCascCutMCList);
    PostData(20, fAntiCascCutMCList);
  }
}
