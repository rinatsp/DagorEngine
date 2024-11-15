// Copyright (C) Gaijin Games KFT.  All rights reserved.
#pragma once

#include "controlType.h"
#include <propPanel/control/container.h>
#include <util/dag_string.h>
#include <imgui/imgui.h>

namespace PropPanel
{

class GroupBoxPropertyControl : public ContainerPropertyControl
{
public:
  GroupBoxPropertyControl(ControlEventHandler *event_handler, ContainerPropertyControl *parent, int id, int x, int y, hdpi::Px w,
    hdpi::Px h, const char caption[]) :
    ContainerPropertyControl(id, event_handler, parent, x, y, w, h), controlCaption(caption)
  {}

  virtual int getImguiControlType() const { return (int)ControlType::GroupBox; }

  virtual unsigned getTypeMaskForSet() const override { return CONTROL_CAPTION; }
  virtual unsigned getTypeMaskForGet() const override { return 0; }

  virtual void setCaptionValue(const char value[]) override { controlCaption = value; }
  virtual void setEnabled(bool enabled) override { controlEnabled = enabled; }
  virtual bool isRealContainer() override { return false; }

  virtual void updateImgui() override { groupBoxUpdateImgui(true); }

  void groupBoxUpdateImgui(bool draw_bottom_separator)
  {
    // NOTE: ImGui porting: the original has drawn a group box around the controls. This is a bit different.

    if (controlCaption.empty())
      ImGui::Separator();
    else
      ImGui::SeparatorText(controlCaption);

    addVerticalSpaceAfterControl();

    ContainerPropertyControl::updateImgui();

    if (draw_bottom_separator)
    {
      addVerticalSpaceAfterControl();
      ImGui::Separator();
    }
  }

protected:
  String controlCaption;
  bool controlEnabled = true;
};

} // namespace PropPanel