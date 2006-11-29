#include "wxsstaticbox.h"

namespace
{
    wxsRegisterItem<wxsStaticBox> Reg(_T("StaticBox"),wxsTWidget,_T("Standard"),50);

    WXS_ST_BEGIN(wxsStaticBoxStyles)
        WXS_ST_CATEGORY("wxStaticBox")
        WXS_ST(wxBU_LEFT)
        WXS_ST(wxBU_TOP)
        WXS_ST(wxBU_RIGHT)
        WXS_ST(wxBU_BOTTOM)
        WXS_ST(wxBU_EXACTFIT)
        WXS_ST_MASK(wxNO_BORDER,wxsSFWin| wxsSFGTK ,0,true)
    WXS_ST_END()

    WXS_EV_BEGIN(wxsStaticBoxEvents)
        WXS_EVI(EVT_BUTTON,wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEvent,Click)
        WXS_EV_DEFAULTS()
    WXS_EV_END()
}

wxsStaticBox::wxsStaticBox(wxsItemResData* Data):
    wxsWidget(
        Data,
        &Reg.Info,
        wxsBaseProperties::flAll,
        wxsStaticBoxEvents,
        wxsStaticBoxStyles,
        _T("")),
    Label(_("Label"))
{}

void wxsStaticBox::OnBuildCreatingCode(wxString& Code,const wxString& WindowParent,wxsCodingLang Language)
{
    switch ( Language )
    {
        case wxsCPP:
        {
            Code<< GetVarName() << _T(" = new wxStaticBox(")
                << WindowParent << _T(",")
                << GetIdName() << _T(",")
                << wxsCodeMarks::WxString(wxsCPP,Label) << _T(",")
                << PosCode(WindowParent,wxsCPP) << _T(",")
                << SizeCode(WindowParent,wxsCPP) << _T(",")
                << StyleCode(wxsCPP) << _T(");\n");
            SetupWindowCode(Code,Language);
            return;
        }

        default:
        {
            wxsCodeMarks::Unknown(_T("wxsStaticBox::OnBuildCreatingCode"),Language);
        }
    }
}

wxObject* wxsStaticBox::OnBuildPreview(wxWindow* Parent,bool Exact,bool)
{
    wxStaticBox* Preview = new wxStaticBox(Parent,GetId(),Label,Pos(Parent),Size(Parent),Style());
    return SetupWindow(Preview,Exact);
}

void wxsStaticBox::OnEnumWidgetProperties(long Flags)
{
    WXS_STRING(wxsStaticBox,Label,0,_("Label"),_T("label"),_T(""),true,false)
}

void wxsStaticBox::OnEnumDeclFiles(wxArrayString& Decl,wxArrayString& Def,wxsCodingLang Language)
{
    switch ( Language )
    {
        case wxsCPP: Decl.Add(_T("<wx/statbox.h>")); return;
        default: wxsCodeMarks::Unknown(_T("wxsStaticBox::OnEnumDeclFiles"),Language);
    }
}
