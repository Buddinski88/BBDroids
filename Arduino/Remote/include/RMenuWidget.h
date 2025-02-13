#if !defined(RMENUWIDGET_H)
#define RMENUWIDGET_H

#include <vector>
#include <functional>
#include <LibBB.h>

#include "Config.h"
#include "RDisplay.h"
#include "RMultiWidget.h"
#include "RLabelWidget.h"
#include "RInput.h"

using namespace bb;

class RMenuWidget: public RMultiWidget {
public:
  RMenuWidget();

  void addEntry(const String& title, std::function<void(void)> callback, int tag=0);
  void clear();

  void up();
  void down();
  void encTurn(float enc);
  void select();
  void resetCursor();

  virtual void takeInputFocus();

  virtual void setSize(uint8_t w, uint8_t h);

protected:
  uint8_t cursor_;
  uint8_t top_;
};


#endif