#include <iostream>
#include <string>

#include "pxr/pxr.h"
#include "pxr/usd/usd/stage.h"
#include "pxr/usd/usd/primRange.h"
#include "pxr/imaging/hd/engine.h"
#include "pxr/usdImaging/usdImagingGL/engine.h"
#include "pxr/usd/usdGeom/camera.h"
#include "pxr/imaging/hdSt/renderDelegate.h"
#include "pxr/usdImaging/usdImaging/delegate.h"

using namespace pxr;

class ColorCorrectionTask final : public HdTask
{
public:
    ColorCorrectionTask()
        : HdTask(SdfPath::AbsoluteRootPath())
    {

    }

    void Execute(HdTaskContext* ctx) override
    {
        std::cout << "(2) Color correcting image" << std::endl;
    }
    void Sync(HdSceneDelegate* delegate,
        HdTaskContext* ctx,
        HdDirtyBits* dirtyBits) override
    {
        std::cout << "Sync" << std::endl;
    }

    virtual void Prepare(HdTaskContext* ctx,
        HdRenderIndex* renderIndex) override
    {
        std::cout << "Prepare" << std::endl;
    }
};

int main(int argc, char* argv[])
{
     // test code
           // Hydra initialization
    HdEngine engine;
    HdStRenderDelegate renderDelegate;
    HdDriver hdDriver;
    HdRenderIndex* renderIndex = HdRenderIndex::New(&renderDelegate, HdDriverVector()); // q1
    UsdImagingDelegate sceneDelegate(renderIndex, SdfPath::AbsoluteRootPath());
    //// Create your task graph
    HdRprimCollection collection; // q2
    HdRenderPassSharedPtr renderPass(renderDelegate.CreateRenderPass(renderIndex, collection));
    HdRenderPassStateSharedPtr renderPassState(renderDelegate.CreateRenderPassState());
    // HdTaskSharedPtr taskRender(new RenderTask(renderPass, renderPassState));
    HdTaskSharedPtr taskColorCorrection(new ColorCorrectionTask());
    HdTaskSharedPtrVector tasks = { taskColorCorrection };
    //// Populate scene graph and generate image
    // sceneDelegate->Populate();
    engine.Execute(renderIndex, &tasks);
    //// Change time causes invalidations, and generate image
    //sceneDelegate->SetTime(1);
    // engine.Execute(renderIndex, &tasks);
    std::cout << "test" << std::endl;
    
}
