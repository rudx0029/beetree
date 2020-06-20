#include "beetree/nodes/helloworld.hpp"
#include "beetree/engine/builder.hpp"
#include "beetree/engine/context.hpp"
#include "beetree/engine/result.hpp"
#include "beetree/startpk/tokens.hpp"

//
// The HelloWorld node is a simple node with no behavior or state. The
// implementation has 2 functions, `loop` and `helloworld` which are described
// further below. The HelloWorld tag being displayed in BeeView is specified in
// the build function `helloworld`.
//
// We use namespaces to identify and group node run-time implementations since
// nodes are defined as a collection of c-style functions (instead of a complex
// inheritance hierarchy). Minimal node implementations typically have a `loop`
// method and build method named after the node. A `setup` method can be added
// if the node needs one time initialization and internal data storage can be
// specified as well, e.g. like internal data in a class.
//
namespace bte {
//
// The `loop` function is where the node's behavior is programmed, e.g. turn
// on an led, command the robot to go forward, or update model paramters.
//
// The function is invoked on every 'tick' of the tree when the node is
// active, e.g. the currently visited node. The node can return 3 values
//     * Running
//     * Success
//     * Fail
// The *Running* return value indicates that the node is still completing
// it's tasks, spanning multiple ticks. When the task is complete the node
// should return a *Success* indicating the task is successful or *Fail* if
// the node's task did not complete or meet the expected behavior.
//
// For node's that tick once, only *Success* or *Fail* need to be returned.
// The HelloWorld node simply returns Success since the HelloWorld tag is read
// when the engine *builds* the node.
//
// Note: `loop` is internal to this implementation file or only has file scope.
//
// Note: Static variables with file scope should not be used in a node's
// implementation. Instead, the designer should specify internal data
// when building the node.
//
static Result loop(Context& context)
{
    //
    return Status::Success;
    //
}

//
// `make_helloworld`is the build function invoked by the engine returning a
// recipe. The recipe informs the engine what the node's tag is to display in
// BeeView and which method to invoke on each tick, i.e. `loop`. There are
// additional options the build function can expose to the engine but that will
// be presented at a later time.
//
// Alright let's try and connect some dots. Looking at the HelloWorld tree,
// there is an instance of the HelloWorld compile time node. The compile time
// node has a reference to the build function `make_helloworld` below. When the
// engine visits the compile time node specified in the tree, the engine
// invokes the compile-time nodes build function, `make_helloworld`. This returns
// the recipe for the run-time node. The engine uses the recipe to read the
// token and send it to BeeView and then invoke the main behavior of the node,
// i.e. `loop()`.
//
Recipe make_helloworld()
{
    return Builder(tokens::HelloWorld,  // the token is read by the engine
                                        // and sent to BeeView when
                                        // building the run-time node
                   loop                 // The builder requires the 'loop' function in order to
                                        // build the run-time node. This tells the engine which
                                        // function to invoke on each tick.
                   )
        .finalize();  // Finalize packages up the information as a recipe for
                      // the engine to use to build the run-time node.
}

}  // namespace bte