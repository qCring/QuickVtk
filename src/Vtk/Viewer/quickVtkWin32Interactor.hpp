#pragma once

#ifdef _MSC_VER

#include <vtkWin32RenderWindowInteractor.h>

namespace quick {

    namespace Vtk {

        class Win32Interactor : public vtkWin32RenderWindowInteractor {
        public:
            vtkTypeMacro(Win32Interactor, vtkWin32RenderWindowInteractor);
            static Win32Interactor* New();
            auto Win32Interactor::Initialize() -> void;
        protected:
            Win32Interactor() = default;
            virtual ~Win32Interactor() = default;
        };
    }
}

#endif