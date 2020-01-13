#include "quickVtkWin32Interactor.hpp"

#ifdef _MSC_VER

#include <vtkWin32OpenGLRenderWindow.h>
#include <vtkObjectFactory.h>

namespace quick {

    namespace Vtk {

        vtkStandardNewMacro(Win32Interactor);

        void Win32Interactor::Initialize() {
            vtkWin32OpenGLRenderWindow* ren;
            int *size;

            if (!this->RenderWindow) {
                vtkErrorMacro(<< "No renderer defined!");
                return;
            }

            if (this->Initialized) {
                return;
            }

            this->Initialized = 1;

            ren = (vtkWin32OpenGLRenderWindow *)(this->RenderWindow);
            ren->Start();
            size = ren->GetSize();
            ren->GetPosition();
            this->WindowId = 0;
            this->Enable();
            this->Size[0] = size[0];
            this->Size[1] = size[1];
        }
    }
}

#endif
