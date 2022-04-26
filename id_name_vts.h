//
// Created by edgallyot on 14/03/2022.
//

#ifndef PINGPONGED_ID_NAME_VTS_H
#define PINGPONGED_ID_NAME_VTS_H

#define PPE_ID_TREE "PingPongEdTree"
#define VTS_PARAMS_N 9

#define PPE_ID_LEFT "leftRate"
#define PPE_NAME_LEFT "Left"
#define PPE_MIN_LEFT 0.0f
#define PPE_MAX_LEFT 3000.0f
#define PPE_DEFAULT_LEFT 0.0f

#define PPE_ID_RIGHT "rightRate"
#define PPE_NAME_RIGHT "Right"
#define PPE_MIN_RIGHT 0.0f
#define PPE_MAX_RIGHT 3000.0f
#define PPE_DEFAULT_RIGHT 0.0f

#define PPE_ID_DRIVE "drive"
#define PPE_NAME_DRIVE "Drive"
#define PPE_MIN_DRIVE 0.0f
#define PPE_MAX_DRIVE 11.0f
#define PPE_DEFAULT_DRIVE 0.0f

#define PPE_ID_FEEDBACK "feedback"
#define PPE_NAME_FEEDBACK "Feedback"
#define PPE_MIN_FEEDBACK 0.0f
#define PPE_MAX_FEEDBACK 150.0f
#define PPE_DEFAULT_FEEDBACK 0.0f

#define PPE_ID_HICUT "hiCut"
#define PPE_NAME_HICUT "High Cut"
#define PPE_MIN_HICUT 0.0f
#define PPE_MAX_HICUT 20000.0f
#define PPE_DEFAULT_HICUT 20000.0f

#define PPE_ID_LOCUT "loCut"
#define PPE_NAME_LOCUT "Low Cut"
#define PPE_MIN_LOCUT 0.0f
#define PPE_MAX_LOCUT 20000.0f
#define PPE_DEFAULT_LOCUT 0.0f

#define PPE_ID_WOW "wow"
#define PPE_NAME_WOW "Wow"
#define PPE_MIN_WOW 0.0f
#define PPE_MAX_WOW 100.0f
#define PPE_DEFAULT_WOW 0.0f

#define PPE_ID_FLUTTER "flutter"
#define PPE_NAME_FLUTTER "Flutter"
#define PPE_MIN_FLUTTER 0.0f
#define PPE_MAX_FLUTTER 100.0f
#define PPE_DEFAULT_FLUTTER 0.0f

#define PPE_ID_MIX "mix"
#define PPE_NAME_MIX "Mix"
#define PPE_MIN_MIX  0.0f
#define PPE_MAX_MIX 100.0f
#define PPE_DEFAULT_MIX 50.0f

enum DelayParameters
{
    Left = 0,
    Right,
    Feedback,
    Drive,
    Hi_Cut,
    Lo_Cut,
    Flutter,
    Wow,
    Mix
};

#endif //PINGPONGED_ID_NAME_VTS_H
