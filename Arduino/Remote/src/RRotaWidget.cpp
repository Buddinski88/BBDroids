#include "RRotaWidget.h"
#include "RRemote.h"

void RRotaWidget::showIndex(unsigned int i) {
    if(i >= widgets_.size()) return;
    index_ = i;
    RRemote::remote.setTopTitle(name());
    widgetsChanged_ = true;
}

RWidget::CursorHint RRotaWidget::cursorHint() {
    RWidget::CursorHint hint = CURSOR_NONE;
    if(index_ != 0 && widgets_.size() > 1) hint = (RWidget::CursorHint)(hint|CURSOR_LEFT);
    if(index_ < widgets_.size()-1) hint = (RWidget::CursorHint)(hint|CURSOR_RIGHT);
    return hint;
}

Result RRotaWidget::draw(ConsoleStream* stream) {
    if(widgets_.size() == 0) return RES_OK;
    if(index_ >= widgets_.size()) index_ = widgets_.size()-1;

    if(widgetsChanged_) {
        widgets_[index_]->setNeedsFullRedraw();
        widgetsChanged_ = false;
    }
    return widgets_[index_]->draw(stream);
}

void RRotaWidget::takeInputFocus() {
    RInput::input.clearCallbacks();
    RInput::input.setTopLeftShortPressCallback([=]{ showPrevious(); });
    RInput::input.setTopRightShortPressCallback([=]{ showNext(); });
}

const String& RRotaWidget::name() {
    if(widgets_.size() == 0 || index_ >= widgets_.size()) return name_;
    return widgets_[index_]->name();
}
