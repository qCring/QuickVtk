#include "vtkOFFReader.h"

#include "vtkCellArray.h"
#include "vtkFloatArray.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkPointData.h"
#include "vtkPolyData.h"
#include "vtkPolygon.h"

#include <QFile>
#include <QTextStream>

vtkStandardNewMacro(vtkOFFReader);

vtkOFFReader::vtkOFFReader() {
    this->FileName = nullptr;
    this->SetNumberOfInputPorts(0);
}

int vtkOFFReader::RequestData(vtkInformation* vtkNotUsed(request), vtkInformationVector** vtkNotUsed(inputVector), vtkInformationVector* outputVector) {
    auto outInfo = outputVector->GetInformationObject(0);
    auto output = vtkPolyData::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));

    if (!this->FileName) {
        vtkErrorMacro(<< "OFFReader: no filename specified");
        return 0;
    }

    std::ifstream in(this->FileName);

    if (!in) {
        vtkErrorMacro(<< "File " << this->FileName << " not found");
        return 0;
    }

    int numberOfVerts = -1;
    int numberOfFaces = -1;
    int numberOfProcessedVerts = 0;
    int numberOfProcessedFaces = 0;

    bool useColors = false;
    bool useNormals = false;

    auto points = vtkPoints::New();
    auto polys = vtkCellArray::New();
    auto colors = vtkSmartPointer<vtkUnsignedCharArray>::New();

    colors->SetNumberOfComponents(3);
    colors->SetName ("Colors");

    QFile inputFile(FileName);

    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);

        int lineNumber = -1;

        while (!in.atEnd()) {
            ++lineNumber;
            auto line = in.readLine().simplified();

            if (line.length() < 1) {
                continue;
            }

            auto values = line.split(" ");

            if (lineNumber == 0) {
                if (line == "COFF") {
                    useColors = true;
                } else if (line == "NOFF") {
                    useNormals = true;
                } else if (values.length() > 1){
                    numberOfVerts = values.at(0).toInt();
                    numberOfFaces = values.at(1).toInt();
                }

                continue;
            }

            if (lineNumber == 1 && numberOfVerts == -1 && numberOfFaces == -1) {
                auto numbers = line.split(" ");

                if (numbers.count() > 1) {
                    numberOfVerts = numbers.at(0).toInt();
                    numberOfFaces = numbers.at(1).toInt();
                }

                continue;
            }

            if (numberOfProcessedVerts < numberOfVerts) {
                if (values.length() < 3) {
                    continue;
                }

                auto x = values[0].toFloat();
                auto y = values[1].toFloat();
                auto z = values[2].toFloat();

                if (useColors) {
                    unsigned char color[3] = {
                        static_cast<unsigned char>(values [3].toInt()),
                        static_cast<unsigned char>(values [4].toInt()),
                        static_cast<unsigned char>(values [5].toInt())
                    };

                    colors->InsertNextTypedTuple(color);
                }

                points->InsertNextPoint(x,y,z);

                ++numberOfProcessedVerts;
            } else if (numberOfProcessedFaces < numberOfFaces) {
                auto poly = vtkPolygon::New();
                poly->GetPointIds()->SetNumberOfIds(values.length());

                for (auto i = 0; i < values.length(); ++i) {
                    poly->GetPointIds()->SetId(i, values.at(i).toInt());
                }
                    
                polys->InsertNextCell(poly);
                poly->Delete();

                ++numberOfProcessedFaces;
            }
        }

        output->SetPoints(points);
        output->SetPolys(polys);

        if (useColors) {
            output->GetPointData()->SetScalars(colors);
        }

        points->Delete();
        polys->Delete();

        inputFile.close();
    }
    
    return 1;
}

vtkOFFReader::~vtkOFFReader() {
    if (this->FileName) {
        delete [] this->FileName;
        this->FileName = nullptr;
    }
}
