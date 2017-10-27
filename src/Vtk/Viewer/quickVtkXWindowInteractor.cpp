#include "quickVtkXWindowInteractor.hpp"

#ifdef __linux__

#include <vtkXOpenGLRenderWindow.h>
#include <vtkObjectFactory.h>

namespace quick {
    
    namespace Vtk {
        
        vtkStandardNewMacro(XWindowInteractor);
        
        void XWindowInteractor::Initialize() {
            vtkXOpenGLRenderWindow* ren;
            int *size;
            
            if (!this->RenderWindow) {
                vtkErrorMacro(<< "No renderer defined!");
                return;
            }
            
            if (this->Initialized) {
                return;
            }
            
            this->Initialized = 1;
            
            ren = (vtkXOpenGLRenderWindow*)(this->RenderWindow);
            ren->Start();
            size = ren->GetSize();
            ren->GetPosition();
            this->Enable();
            this->Size[0] = size[0];
            this->Size[1] = size[1];
        }
    }
}

#endif
