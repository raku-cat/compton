#include "windowlist.h"

#include "window.h"

void windowlist_draw(session_t* ps, win* head, float* z) {
    glx_mark(ps, head, true);
    (*z) = 1;
    for (win *w = head; w; w = w->next_trans) {

        if(w->a.map_state == IsViewable) {
            win_draw(ps, w, *z);
        }

        // @HACK: This shouldn't be hardcoded. As it stands, it will probably break
        // for more than 1k windows
        (*z) -= .0001;
    }
    glx_mark(ps, head, false);
}