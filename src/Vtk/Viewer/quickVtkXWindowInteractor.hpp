#pragma once

#ifdef __linux__

#include <vtkXRenderWindowInteractor.h>

namespace quick {
    
    namespace Vtk {
        
        class XWindowInteractor : public vtkXRenderWindowInteractor {
        public:
            vtkTypeMacro(XWindowInteractor, vtkXRenderWindowInteractor);
            static XWindowInteractor* New();
            auto XWindowInteractor::Initialize() -> void;
        protected:
            XWindowInteractor() = default;
            virtual ~XWindowInteractor() = default;
        };
    }
}

#endif

