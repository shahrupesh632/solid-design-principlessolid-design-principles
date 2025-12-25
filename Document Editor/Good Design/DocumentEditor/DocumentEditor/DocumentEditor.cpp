// DocumentEditor.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// Abstraction of Document Elements
class DocumentElement {
public:
    virtual std::string render() = 0;
};

//Conceret implementation for Text element
class TextElement : public DocumentElement {
private:
    std::string text;

public:
    TextElement(std::string text)
    {
        this->text = text;
    }

    std::string render() override {
        return text;
    }
};

// conceret Implemenataion for Image Element
class ImageElement :public DocumentElement {
private:
    std::string imagePath;

public:
    ImageElement(std::string imagePath) {
        this->imagePath = imagePath;
    }

    std::string render() override {
        return "[Image: " + imagePath + "]";
    }
};
// NewLineElement represents a line break in the document.
class NewLineElement : public DocumentElement {
public:
    std::string render() override {
        return "\n";
    }
};

// TabSpaceElement represents a tab space in the document.
class TabElement : public DocumentElement {
public:
    std::string render() override {
        return "\t";
    }
};

// Document class responsible for holding a collection of elements
class Document {
private:
    std::vector<DocumentElement*> elements;

public:
    void addElement(DocumentElement* element) {
        elements.push_back(element);
    }

    // Renders the document by concatenating the render output of all elements.
    std::string render() {
        std::string result;
        for (auto element : elements) {
            result += element->render();
        }
        return result;
    }
};

// Persistence abstraction
class Persistence {
public:
    virtual void save(std::string data) = 0;
};

//FileStorage class implementation
class FileStorage : public Persistence {
public:
    void save(std::string data) override{
        std::ofstream outfile("document.txt");
        if (outfile) {
            outfile << data;
            outfile.close();
            std::cout << "Document save successfully in document.txt" << std::endl;
        }
        else {
            std::cout << "Error: Unable to open the file for writing." << std::endl;
        }
    }
};

// Placeholder DBStorage implementation
class DBStorage : public Persistence {
public:
    void save(std::string data) override {
        std::cout << "Document saved successfully in Database." << std::endl;
    }
};

// DocumentEditor class managing client interactions
class DocumentEditor {
private:
    Document* document;
    Persistence* storage;
    std::string renderedDocument;

public:
    DocumentEditor(Document* document, Persistence* storage) {
        this->document = document;
        this->storage = storage;
    }

    void addText(std::string text) {
        document->addElement(new TextElement(text));
    }

    void addImage(std::string imagePath) {
        document->addElement(new ImageElement(imagePath));
    }

    void addNewLine() {
        document->addElement(new NewLineElement());
    }

    void addTabSpace() {
        document->addElement(new TabElement());
    }

    std::string renderDocument() {
        if (renderedDocument.empty()) {
            renderedDocument = document->render();
        }
        return renderedDocument;
    }

    void saveDocument() {
        storage->save(renderDocument());
    }
};
int main()
{
    Document* doc = new Document();
    Persistence* persistence = new FileStorage();
    DocumentEditor* editor = new DocumentEditor(doc, persistence);

    editor->addText("Hello World!");
    editor->addNewLine();
    editor->addText("This is a real-world document editor example.");
    editor->addNewLine();
    editor->addTabSpace();
    editor->addText("Indented text after a tab space.");
    editor->addNewLine();
    editor->addImage("picture.png");

    std::cout << editor->renderDocument() << std::endl;
    editor->saveDocument();
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
