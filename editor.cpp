#include "editor.hpp"
#include "DIRenderer/camera.hpp"
#include "DIPhysics/collider.hpp"
#include "DIDebuger/log.hpp"
#include "DIRenderer/mesh.hpp"
#include "DIRenderer/renderer.hpp"
#include "DIWindow/viewport.hpp"
#include "DIWindow/win.hpp"
#include "DIParser/font.hpp"

namespace DI{

    Editor* Editor::m_instance = 0;
    extern WinData* eg_winData;

    void Editor::Init(){
        DI_LOG_TRACE("Editor say: Init editor.");
        m_instance = new Editor();
        m_instance->interfacer = InterfacerSingleton::GetInstance();
        // Rearange viewports
        ViewportHandler::SetStickTo(ViewportsSupportedID::MAIN_VIEWPORT,ViewportsSupportedID::VIEWPORT_ONE, ViewportStickSide::VIEWPORT_TOP, 25);
        ViewportHandler::SetStickTo(ViewportsSupportedID::MAIN_VIEWPORT,ViewportsSupportedID::VIEWPORT_TWO, ViewportStickSide::VIEWPORT_RIGHT, 400);
        ViewportHandler::SetStickTo(ViewportsSupportedID::MAIN_VIEWPORT,ViewportsSupportedID::VIEWPORT_THREE, ViewportStickSide::VIEWPORT_BOTTOM, 25);
        ViewportHandler::SetStickTo(ViewportsSupportedID::MAIN_VIEWPORT,ViewportsSupportedID::VIEWPORT_FOUR, ViewportStickSide::VIEWPORT_LEFT, 25);
        // Set callbacks for Editor viewports
        ViewportHandler::Set(DI::ViewportsSupportedID::VIEWPORT_ONE,std::bind(&Editor::UpdateTopViewport,m_instance,std::placeholders::_1));
        ViewportHandler::Set(DI::ViewportsSupportedID::VIEWPORT_TWO,std::bind(&Editor::UpdateRightViewport,m_instance,std::placeholders::_1));
        ViewportHandler::Set(DI::ViewportsSupportedID::VIEWPORT_THREE,std::bind(&Editor::UpdateBottomViewport,m_instance,std::placeholders::_1));
        ViewportHandler::Set(DI::ViewportsSupportedID::VIEWPORT_FOUR,std::bind(&Editor::UpdateLeftViewport,m_instance,std::placeholders::_1));

        m_instance->button1 = new TextButton("Some",glm::vec2(50,15),glm::vec2(30,30));
        m_instance->button1->SetCallback(PRESSED, std::bind(&Editor::FilePressed,m_instance));
        m_instance->interfacer->Add(m_instance->button1, VIEWPORT_THREE);
        m_instance->slider = new HorizontalSlider(glm::vec2(300,300),-100,100, 0);

        m_instance->interfacer->Add(m_instance->slider, VIEWPORT_TWO);
        m_instance->input = new StringInput(glm::vec2(200,100),glm::vec2(10,10),"Input");
        m_instance->interfacer->Add(m_instance->input, VIEWPORT_TWO);
        m_instance->checkbox = new TextCheckbox("Checkbox",glm::vec2(200,500));
        m_instance->interfacer->Add(m_instance->checkbox, VIEWPORT_TWO);
    }
    void Editor::Kill(){
        DI_LOG_TRACE("Editor say: Kill editor.");
        ViewportHandler::UnSet(ViewportsSupportedID::VIEWPORT_ONE);
        ViewportHandler::UnSet(ViewportsSupportedID::VIEWPORT_TWO);
        ViewportHandler::UnSet(ViewportsSupportedID::VIEWPORT_THREE);
        ViewportHandler::UnSet(ViewportsSupportedID::VIEWPORT_FOUR);

        delete m_instance;
    }


    void Editor::UpdateTopViewport(ViewportData* data){
      CameraHandler::Use(*interfacer->GetCamera(), *data);
      for (const auto& unit : data->units){
        RendererSingleton::GetInstance()->Draw(*unit);
      }
    }
    void Editor::UpdateBottomViewport(ViewportData* data){
      CameraHandler::Use(*interfacer->GetCamera(), *data);
      for (const auto& unit : data->units){
        RendererSingleton::GetInstance()->Draw(*unit);
      }
    }
    void Editor::UpdateRightViewport(ViewportData* data){
      CameraHandler::Use(*interfacer->GetCamera(), *data);
      for (const auto& unit : data->units){
        RendererSingleton::GetInstance()->Draw(*unit);
      }
    }
    void Editor::UpdateLeftViewport(ViewportData* data){
      CameraHandler::Use(*interfacer->GetCamera(), *data);
      for (const auto& unit : data->units){
        RendererSingleton::GetInstance()->Draw(*unit);
      }
    }
    
    
    
    
    void Editor::FilePressed(){
      DI_LOG_INFO("FIle pressed");
      //isFile = !isFile;
      //DI_LOG_INFO("FIle pressed");
      //if (isFile){
      //  CreateFilePopup();
      //}
      //else{
      //  interfacer->Remove(popup);
      //}
    }
    void Editor::SettingsPressed(){
      isSettings = !isSettings;
      if (isSettings){
        CreateSettingsPopup();
      }
      else{
        interfacer->Remove(popup);
      }
    }
    void Editor::MorePressed(){
      isMore = !isMore;
      if (isMore){
        CreateMorePopup();
      }
      else{
        interfacer->Remove(popup);
      }
    }  
    void Editor::CreateTopPane(){
      DI::TextButton* btn = new DI::TextButton("File",glm::vec2(100,0),glm::vec2(30,10));
      btn->SetSize(glm::vec2(100,30));
      btn->SetCallback(DI::PRESSED,std::bind(&Editor::FilePressed,this));
      btn->SetPosition(glm::vec2(100,100));

      DI::TextButton* btn1 = new DI::TextButton("Settings",glm::vec2(0),glm::vec2(30,10));
      btn1->SetCallback(DI::PRESSED,std::bind(&Editor::SettingsPressed,this));
      btn1->SetSize(glm::vec2(150,30));
      btn1->SetPosition(glm::vec2(interfacer->GetCamera()->GetRight()/-2 + btn->GetSize().x + btn1->GetSize().x/2 + 20,0));
    
      DI::TextButton* btn2 = new DI::TextButton("More",glm::vec2(0),glm::vec2(30,10));
      btn2->SetCallback(DI::PRESSED,std::bind(&Editor::MorePressed,this));
      btn2->SetSize(glm::vec2(100,30));
      btn2->SetPosition(glm::vec2(interfacer->GetCamera()->GetRight()/-2 + btn->GetSize().x + btn1->GetSize().x + btn2->GetSize().x/2 + 30,0));
    
      topPane = new DI::Pane(DI::StickySide::TOP_SIDE,glm::vec2(interfacer->GetCamera()->GetRight(),50));
      topPane->SetPadding(5);
      topPane->SetStickTo(DI::StickySide::TOP_SIDE);
      topPane->Add(btn,DI::ViewportsSupportedID::VIEWPORT_ONE);
      topPane->Add(btn1,DI::ViewportsSupportedID::VIEWPORT_ONE);
      topPane->Add(btn2,DI::ViewportsSupportedID::VIEWPORT_ONE);
      interfacer->Add(topPane,DI::ViewportsSupportedID::VIEWPORT_ONE);
    }
    void Editor::CreateRightPane(){
      isViewer = !isViewer;
      if (isViewer){
        rightPane = new DI::Pane(DI::StickySide::RIGHT_SIDE,glm::vec2(interfacer->GetCamera()->GetRight()/4,interfacer->GetCamera()->GetTop() - topPane->GetSize().y));
        rightPane->SetPadding(5);
        rightPane->SetOffset(glm::vec2(rightPane->GetOffset().x,(-1)*topPane->GetSize().y/2));
        rightPane->SetStickTo(DI::StickySide::RIGHT_SIDE);
        rightPane->GetPrimitive()->SetColor(glm::vec4(1,1,1,1));
        DI::Lable* l1 = new DI::Lable(glm::vec2(0),"Simple Model Viewer");
        l1->GetPrimitive()->SetColor(rightPane->GetPrimitive()->GetColor());
        rightPane->Add(l1,DI::ViewportsSupportedID::VIEWPORT_TWO);
        interfacer->Add(rightPane,DI::ViewportsSupportedID::VIEWPORT_TWO);
      }
      else{
        interfacer->Remove(rightPane);
      }
    } 
    void Editor::CreateFilePopup(){
      DI::TextButton* quit = new DI::TextButton("Quit",glm::vec2(0),glm::vec2(0));
      quit->SetSize(glm::vec2(100,30));
      quit->SetCallback(DI::GUIState::PRESSED,[&](){
        eg_winData->isOpen = false;
      });
      DI::TextButton* load = new DI::TextButton("Load",glm::vec2(0),glm::vec2(0));
      load->SetSize(glm::vec2(100,30));
      load->SetCallback(DI::GUIState::PRESSED,[&](){

      });

      popup = new DI::Popup(glm::vec2(0),glm::vec2(0));
      popup->Add(quit,DI::ViewportsSupportedID::VIEWPORT_ONE);
      popup->Add(load,DI::ViewportsSupportedID::VIEWPORT_ONE);
      popup->UpdateSize();
      popup->UpdatePosition();
      int x = popup->GetSize().x/2.f + topPane->GetPadding()*2;
      int y = interfacer->GetCamera()->GetTop() - popup->GetSize().y/2.f - topPane->GetSize().y - topPane->GetPadding();
      popup->SetPosition(glm::vec2(x,y));
      popup->UpdateSize();
      popup->UpdatePosition();
      interfacer->Add(popup,DI::ViewportsSupportedID::VIEWPORT_ONE);
    }
    void Editor::CreateSettingsPopup(){
      popup = new DI::Popup(glm::vec2(0),glm::vec2(0));
      glm::vec4 color = popup->GetPrimitive()->GetColor();
      DI::TextButton* hide = new DI::TextButton("Hide all",glm::vec2(0),glm::vec2(0));
      DI::TextCheckbox* viewer = new DI::TextCheckbox("Show viewer",glm::vec2(0));
      viewer->GetBackground()->SetColor(color);
      DI::TextCheckbox* simplUI = new DI::TextCheckbox("Use simple UI",glm::vec2(0));
      simplUI->GetBackground()->SetColor(color);
      DI::TextCheckbox* debug = new DI::TextCheckbox("Debug mode",glm::vec2(0));
      debug->GetBackground()->SetColor(color);

      popup->Add(viewer,DI::ViewportsSupportedID::VIEWPORT_ONE);
      popup->Add(simplUI,DI::ViewportsSupportedID::VIEWPORT_ONE);
      popup->Add(debug,DI::ViewportsSupportedID::VIEWPORT_ONE);
      popup->Add(hide,DI::ViewportsSupportedID::VIEWPORT_ONE);
      popup->UpdateSize();
      popup->UpdatePosition();
      int x = popup->GetSize().x/2.f*2 + topPane->GetPadding()*2;
      int y = interfacer->GetCamera()->GetTop() - popup->GetSize().y/2.f - topPane->GetSize().y - topPane->GetPadding();
      popup->SetPosition(glm::vec2(x,y));
      popup->UpdateSize();
      popup->UpdatePosition();
      interfacer->Add(popup,DI::ViewportsSupportedID::VIEWPORT_ONE);
    }
    void Editor::CreateMorePopup(){
      popup = new DI::Popup(glm::vec2(0),glm::vec2(0));
      glm::vec4 color = popup->GetPrimitive()->GetColor();
      DI::Lable* l1 = new DI::Lable(glm::vec2(0),"Hi I'm developer of");
      l1->GetPrimitive()->SetColor(color);
      DI::Lable* l2 = new DI::Lable(glm::vec2(0),"SMP. You can reach me by:");
      l2->GetPrimitive()->SetColor(color);
      DI::Lable* l3 = new DI::Lable(glm::vec2(0),"email: ChedrDen@gmail.com");
      l3->GetPrimitive()->SetColor(color);
      DI::Lable* l4 = new DI::Lable(glm::vec2(0),"github: DmRafaule");
      l4->GetPrimitive()->SetColor(color);

      popup->Add(l1,DI::ViewportsSupportedID::VIEWPORT_ONE);
      popup->Add(l2,DI::ViewportsSupportedID::VIEWPORT_ONE);
      popup->Add(l3,DI::ViewportsSupportedID::VIEWPORT_ONE);
      popup->Add(l4,DI::ViewportsSupportedID::VIEWPORT_ONE);
      popup->UpdateSize();
      popup->UpdatePosition();
      int x = interfacer->GetCamera()->GetRight()/2;
      int y = interfacer->GetCamera()->GetTop()/2;
      popup->SetPosition(glm::vec2(x,y));
      popup->UpdateSize();
      popup->UpdatePosition();
      interfacer->Add(popup,DI::ViewportsSupportedID::VIEWPORT_ONE);
    } 
}
