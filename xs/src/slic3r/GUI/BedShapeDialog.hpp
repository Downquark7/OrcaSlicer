// The bed shape dialog.
// The dialog opens from Print Settins tab->Bed Shape : Set...

#include "OptionsGroup.hpp"
#include "2DBed.hpp"


#include <wx/dialog.h>
#include <wx/choicebk.h>

namespace Slic3r {
namespace GUI {

using ConfigOptionsGroupShp = std::shared_ptr<ConfigOptionsGroup>;
class BedShapePanel : public wxPanel
{
	wxChoicebook*	m_shape_options_book;
	Bed_2D*			m_canvas;

	std::vector <ConfigOptionsGroupShp>	m_optgroups;

public:
	BedShapePanel(wxWindow* parent) : wxPanel(parent, wxID_ANY){}
	~BedShapePanel(){}

	void		build_panel(ConfigOptionPoints* default_pt);
	
	ConfigOptionsGroupShp	init_shape_options_page(std::string title);
	void		set_shape(ConfigOptionPoints* points);
	void		update_preview();
	void		update_shape();
	void		load_stl();
	
	// Returns the resulting bed shape polygon. This value will be stored to the ini file.
	std::vector<Pointf>	GetValue() { return m_canvas->m_bed_shape; }
};

class BedShapeDialog : public wxDialog
{
	BedShapePanel*	m_panel;
	wxLocale*		m_Locale;
	wxApp*			m_App;
public:
	BedShapeDialog(wxWindow* parent) : wxDialog(parent, wxID_ANY, "Bed Shape",
		wxDefaultPosition, wxSize(350, 700), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER){}
	~BedShapeDialog(){ if (m_Locale){ wxDELETE(m_Locale);} }

	void		build_dialog(ConfigOptionPoints* default_pt);
	std::vector<Pointf>	GetValue() { return m_panel->GetValue(); }

	bool	LoadLanguage();
	void	GetInstalledLanguages(wxArrayString & names, wxArrayLong & identifiers);
};

} // GUI
} // Slic3r
