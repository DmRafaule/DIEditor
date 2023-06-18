#pragma once

#include "DIGUI/button.hpp"
#include "DIGUI/checkbox.hpp"
#include "DIGUI/input.hpp"
#include "DIGUI/interface.hpp"
#include "DIPrimitives/primitives.hpp"
#include "DIGUI/slider.hpp"

namespace DI{

    struct ViewportData;
    class InterfacerSingleton;
    class Pane;
    class Popup;

    class Editor{
    friend class Engine;
    private:
        Editor(){};

        static void Init();
        static void Kill();
        void UpdateTopViewport(ViewportData* data);
        void UpdateBottomViewport(ViewportData* data);
        void UpdateRightViewport(ViewportData* data);
        void UpdateLeftViewport(ViewportData* data);
        // This is temporarely func
        void CreateTopPane();
        void CreateRightPane();
        void CreateFilePopup();
        void CreateSettingsPopup();
        void CreateMorePopup();
        void FilePressed();
        void SettingsPressed();
        void MorePressed();
    private:
        static Editor* m_instance;
        bool isFile = false;
        bool isSettings = false;
        bool isMore = false;
        bool isAlt = false;
        bool isViewer = false;
        InterfacerSingleton* interfacer;
        Reqtangle* button;
        TextButton* button1;
        HorizontalSlider* slider;
        StringInput* input;
        TextCheckbox* checkbox;
        Text* text;
        Pane* topPane;
        Pane* rightPane;
        Popup* popup;
    public:
        inline static const Editor* GetInstance(){ return m_instance; }
    };

}