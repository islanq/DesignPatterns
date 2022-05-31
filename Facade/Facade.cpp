#include <ostream>
#include <iostream>

using std::cout;
using std::endl;


class MiscDepartment {
public:

  explicit MiscDepartment()
    : _state{0} {}

  auto SubmitNetworkRequest()->void {
    _state = 0;
  }

  auto CheckOnStatus()->bool
  {
    _state++;
    return _state == Complete ? true : false;
  }

private:

  enum States {
    Received,
    DenyAllKnowledge,
    ReferClientToFacilities,
    FacilitiesHasNotSentPaperwork,
    ElectricianIsNotDone,
    ElectricianDidItWrong,
    DispatchTechnician,
    SignedOff,
    DoesNotWork,
    FixElectriciansWiring,
    Complete
  };
  int _state;
};

class ElectricianUnion {
public:

  explicit ElectricianUnion()
    : _state{0} {}

  auto SubmitNetworkRequest()->void {
    _state = 0;
  }

  auto CheckOnStatus()->bool
  {
    _state++;
    return _state == Complete ? true : false;
  }

private:

  enum States {
    Received,
    RejectTheForm,
    SizeTheJob,
    SmokeAndJokeBreak,
    WaitForAuthorization,
    DoTheWrongJob,
    BlameTheEngineer,
    WaitToPunchOut,
    DoHalfAJob,
    ComplainToEngineer,
    GetClarification,
    CompleteTheJob,
    TurnInThePaperwork,
    Complete
  };
  int _state;
};

class FacilitiesDepartment {
public:

  explicit FacilitiesDepartment()
    : _state{0} {}

  auto SubmitNetworkRequest()->void {
    _state = 0;
  }

  auto CheckOnStatus()->bool
  {
    _state++;
    return _state == Complete;
  }

private:

  enum States {
    Received,
    AssignToEngineer,
    EngineerResearches,
    RequestIsNotPossible,
    EngineerLeavesCompany,
    AssignToNewEngineer,
    NewEngineerResearches,
    ReassignEngineer,
    EngineerReturns,
    EngineerResearchesAgain,
    EngineerFillsOutPaperWork,
    Complete
  };
  int _state;
};

class FacilitiesFacade {
public:

  FacilitiesFacade()
    : _state{0}
    , _count{0} {}

  auto SubmitNetworkRequest()->void {
    _state = 0;
  }

  auto CheckOnStatus()->bool
  {
    _count++;

    /* Job request has just been received */
    if (_state == Received) {
      _state++;

      /* Forward the job request to the engineer */
      _engineer.SubmitNetworkRequest();
      cout << "submitted to Facilities - " << _count <<
        " phone calls so far" << endl;
    } else if (_state == SubmitToEngineer) {
      /* If engineer is complete, forward to electrician */
      if (_engineer.CheckOnStatus()) {
        _state++;
        _electrician.SubmitNetworkRequest();
        cout << "submitted to Electrician - " << _count <<
          " phone calls so far" << endl;
      }
    } else if (_state == SubmitToElectrician) {
      /* If electrician is complete, forward to technician */
      if (_electrician.CheckOnStatus()) {
        _state++;
        _technician.SubmitNetworkRequest();
        cout << "submitted to MIS - " << _count <<
          " phone calls so far" << endl;
      }
    } else if (_state == SubmitToTechnician) {
      /* If technician is complete, job is done */
      if (_technician.CheckOnStatus()) return true;
    }

    /* The job is not entirely complete */
    return false;
  }

  auto GetNumberOfCalls() const->int {
    return _count;
  }

private:

  enum States {
    Received,
    SubmitToEngineer,
    SubmitToElectrician,
    SubmitToTechnician
  };

  int _state, _count;
  FacilitiesDepartment _engineer;
  ElectricianUnion _electrician;
  MiscDepartment _technician;
};

auto main()->int
{
  FacilitiesFacade facilities;

  facilities.SubmitNetworkRequest();


  /* Keep checking until job is complete */
  while (!facilities.CheckOnStatus()) {
    cout << "job completed after only "
         << facilities.GetNumberOfCalls()
         << " phone calls" << endl;
  }

  getchar();
  return EXIT_SUCCESS;
}
