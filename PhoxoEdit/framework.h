#pragma once

#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // remove support for MFC controls in dialogs
#define _AFX_ALL_WARNINGS       // turns off MFC's hiding of some common and often safely ignored warning messages

// Lib BCG
#include "BCGCBProInc.h"

// Lib PhoXo Core & UIStone，这是最基础的库
#include "../3rd/phoxo-core-lib/src/phoxo_core.h" 
#define PHOXO_LANGUAGE_BASE_FOLDER LR"(language\edit\)";
#include "../3rd/UIStone/UIStone.h"

#include "canvas/canvas.h"
#include "canvas/mfc_scroll_view_anchor_restore.h"
using phoxo::ScrollViewDrawContext, phoxo::ScrollViewAnchorRestore;

using FCColor = phoxo::Color;
using FCImage = phoxo::Image;
using CStringRef = const CString&;

using std::unique_ptr, std::make_unique;
using std::shared_ptr, std::make_shared;
using phoxo::GPointF;
using phoxo::Canvas;
using phoxo::Layer;

//-----------------------------------------------------------------------------
#include "phoxo_shared.h"

#include "base/app_define.h"
#include "base/app_config.h"
#include "tool_base.h"

#include "resource.h"       // main symbols
#pragma comment (lib, "../modules/image/bin/image.lib")
