#pragma once

#ifdef __linux__

#include <vtkGenericRenderWindowInteractor.h>

namespace quick {
    
    namespace Vtk {
        
        class GenericInteractor : public vtkGenericRenderWindowInteractor {
        public:
            vtkTypeMacro(GenericInteractor, vtkGenericRenderWindowInteractor);
            static GenericInteractor* New();
            auto Initialize() -> void override;
        protected:
            GenericInteractor() = default;
            virtual ~GenericInteractor() = default;
        };
    }
}

#endif
