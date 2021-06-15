#include "beetree/engine/select-algorithm.hpp"
#include "beetree/engine/branch-reader.hpp"

namespace bte {
namespace {
using BranchIterator = BranchReader::const_iterator;
}

void SelectAlgorithm::setup(const Node&      node,
                            /*in,out*/ Data& data)
{
    BranchIterator iter = BranchReader::begin(node);
    if (iter)
    {
        data.iter   = iter;
        data.status = Status::Running;
    }
    else
    {
        data.status = Status::Fail;
    }
}

Result SelectAlgorithm::loop(const Node&      node,
                             /*in,out*/ Data& data)
{
    Status         status   = Status::Fail;
    const Node*    branch   = nullptr;
    BranchIterator end_iter = BranchReader::end(node);

    if (data.iter && end_iter)
    {
        if (Status::Running == data.status)
        {
            if (data.iter != end_iter)
            {
                // iterate through the next node
                status = data.status;
                branch = *data.iter;
                data.iter++;
            }
            else
            {
                // made through all of the nodes unsuccessfully
                // mark result as fail
                status = Status::Fail;
                branch = nullptr;
            }
        }
        else
        {
            // we're otherwise done, report the branch's status
            // this should be success.
            status = data.status;
        }
    }

    return {status, branch};
}

void SelectAlgorithm::update(Status branch_status, /*in,out*/ Data& data)
{
    // if branch is successful, then we are done
    // mark result as success
    if (branch_status == Status::Success)
    {
        data.status = Status::Success;
    }
}
}  // namespace bte