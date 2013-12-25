//======================================================================
//  comptext; main
//    Author: Dave Freese, W1HKJ <w1hkj@w1hkj.com>
//
//  based on the program RTTY Compare by
//    Alex Shovkoplyas, VE3NEA ve3nea@dxatlas.com
//  Original written in Pascal and distributed only for Windows OS
//
//  This program is distributed under the GPL license
//======================================================================

#include "comp_ui.h"
#include "comp_txt.h"

extern Fl_Double_Window *main_window;

int main(int argc, char **argv) {
	make_comptext_win();
	main_window->show(argc, argv);
	return Fl::run();
}
