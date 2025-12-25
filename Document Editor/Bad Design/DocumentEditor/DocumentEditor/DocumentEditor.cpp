// This is the document editor. This is the example of bad Design. We are writing every functions in one class

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class DocumentEditor {
private:
    std::vector<std::string> documentElements;
    std::string renderedDocument;
    
public:
    // Adds Text as a plain string
    void addText(std::string text) {
        documentElements.push_back(text);
    }

    //Adds an image represented by its file path
    void addImage(std::string imagePath) {
        documentElements.push_back(imagePath);
    }

    std::string renderDocument() {
        if (renderedDocument.empty()) {
            std::string result;
            for (auto element : documentElements) {
                if (element.size() > 4 && (element.substr(element.size() - 4) == ".jpg" ||
                    element.substr(element.size() - 4) == ".png")) {
                    result += "[Image: " + element + "]" + "\n";
                }
                else {
                    result += element + "\n";
                }
            }
            renderedDocument = result;
        }

        return renderedDocument;
    }

    void saveToFile() {
        std::ofstream file("document.txt");
        if (file.is_open()) {
            file << renderDocument();
            file.close();
            std::cout << "Document saved to document.txt" << std::endl;
        }
        else {
            std::cout << "Error: Unable to open file for writing." << std::endl;
        }
    }

};
int main()
{
    DocumentEditor editor;
    editor.addText("Hello, world!");
    editor.addImage("picture.png");
    editor.addText("This is a document editor.");

    std::cout << editor.renderDocument() << std::endl;
    editor.saveToFile();
    std::getchar();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
