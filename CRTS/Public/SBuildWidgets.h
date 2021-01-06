#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

//TODO DELETE
class CRTS_API SBuildWidgets : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBuildWidgets)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
