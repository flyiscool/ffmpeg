#include "mi_panel_datatype.h"

#define FLAG_DELAY            0xFE
#define FLAG_END_OF_TABLE     0xFF   // END OF REGISTERS MARKER

#define HPW (5)
#define HBP (60)
#define HFP (40)
#define VPW (3) 
#define VBP (11)
#define VFP (15)

#define FPS (60)
#define HDA (720)
#define VDA (1280)


MI_PANEL_ParamConfig_t stPanelParam =
{
    "ST7703_720X1280_60", // const char *m_pPanelName;                ///<  PanelName
    0, //MS_U8 m_bPanelDither :1;                 ///<  PANEL_DITHER, keep the setting
    E_MI_PNL_LINK_MIPI_DSI, //MHAL_DISP_ApiPnlLinkType_e m_ePanelLinkType   :4;  ///<  PANEL_LINK

    ///////////////////////////////////////////////
    // Board related setting
    ///////////////////////////////////////////////
    1,  //MS_U8 m_bPanelDualPort  :1;              ///<  VOP_21[8], MOD_4A[1],    PANEL_DUAL_PORT, refer to m_bPanelDoubleClk
    0,  //MS_U8 m_bPanelSwapPort  :1;              ///<  MOD_4A[0],               PANEL_SWAP_PORT, refer to "LVDS output app note" A/B channel swap
    0,  //MS_U8 m_bPanelSwapOdd_ML    :1;          ///<  PANEL_SWAP_ODD_ML
    0,  //MS_U8 m_bPanelSwapEven_ML   :1;          ///<  PANEL_SWAP_EVEN_ML
    0,  //MS_U8 m_bPanelSwapOdd_RB    :1;          ///<  PANEL_SWAP_ODD_RB
    0,  //MS_U8 m_bPanelSwapEven_RB   :1;          ///<  PANEL_SWAP_EVEN_RB

    0,  //MS_U8 m_bPanelSwapLVDS_POL  :1;          ///<  MOD_40[5], PANEL_SWAP_LVDS_POL, for differential P/N swap
    0,  //MS_U8 m_bPanelSwapLVDS_CH   :1;          ///<  MOD_40[6], PANEL_SWAP_LVDS_CH, for pair swap
    0,  //MS_U8 m_bPanelPDP10BIT      :1;          ///<  MOD_40[3], PANEL_PDP_10BIT ,for pair swap
    1,  //MS_U8 m_bPanelLVDS_TI_MODE  :1;          ///<  MOD_40[2], PANEL_LVDS_TI_MODE, refer to "LVDS output app note"

    ///////////////////////////////////////////////
    // For TTL Only
    ///////////////////////////////////////////////
    0,  //MS_U8 m_ucPanelDCLKDelay;                ///<  PANEL_DCLK_DELAY
    0,  //MS_U8 m_bPanelInvDCLK   :1;              ///<  MOD_4A[4],                   PANEL_INV_DCLK
    0,  //MS_U8 m_bPanelInvDE     :1;              ///<  MOD_4A[2],                   PANEL_INV_DE
    0,  //MS_U8 m_bPanelInvHSync  :1;              ///<  MOD_4A[12],                  PANEL_INV_HSYNC
    0,  //MS_U8 m_bPanelInvVSync  :1;              ///<  MOD_4A[3],                   PANEL_INV_VSYNC

    ///////////////////////////////////////////////
    // Output driving current setting
    ///////////////////////////////////////////////
    // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
    1,  //MS_U8 m_ucPanelDCKLCurrent;              ///<  define PANEL_DCLK_CURRENT
    1,  //MS_U8 m_ucPanelDECurrent;                ///<  define PANEL_DE_CURRENT
    1,  //MS_U8 m_ucPanelODDDataCurrent;           ///<  define PANEL_ODD_DATA_CURRENT
    1,  //MS_U8 m_ucPanelEvenDataCurrent;          ///<  define PANEL_EVEN_DATA_CURRENT

    ///////////////////////////////////////////////
    // panel on/off timing
    ///////////////////////////////////////////////
    30,  //MS_U16 m_wPanelOnTiming1;                ///<  time between panel & data while turn on power
    400,  //MS_U16 m_wPanelOnTiming2;                ///<  time between data & back light while turn on power
    80,  //MS_U16 m_wPanelOffTiming1;               ///<  time between back light & data while turn off power
    30,  //MS_U16 m_wPanelOffTiming2;               ///<  time between data & panel while turn off power

    ///////////////////////////////////////////////
    // panel timing spec.
    ///////////////////////////////////////////////
    // sync related
    HPW,  //MS_U8 m_ucPanelHSyncWidth;               ///<  VOP_01[7:0], PANEL_HSYNC_WIDTH
    HBP,  //MS_U8 m_ucPanelHSyncBackPorch;           ///<  PANEL_HSYNC_BACK_PORCH, no register setting, provide value for query only

                                             ///<  not support Manuel VSync Start/End now
                                             ///<  VOP_02[10:0] VSync start = Vtt - VBackPorch - VSyncWidth
                                             ///<  VOP_03[10:0] VSync end = Vtt - VBackPorch
    VPW,  //MS_U8 m_ucPanelVSyncWidth;               ///<  define PANEL_VSYNC_WIDTH
    VBP,  //MS_U8 m_ucPanelVBackPorch;               ///<  define PANEL_VSYNC_BACK_PORCH

    // DE related
    (HPW+HBP),  //MS_U16 m_wPanelHStart;                   ///<  VOP_04[11:0], PANEL_HSTART, DE H Start (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
    (VPW+VBP),  //MS_U16 m_wPanelVStart;                   ///<  VOP_06[11:0], PANEL_VSTART, DE V Start
    HDA,  //MS_U16 m_wPanelWidth;                    ///< PANEL_WIDTH, DE width (VOP_05[11:0] = HEnd = HStart + Width - 1)
    VDA,  //MS_U16 m_wPanelHeight;                   ///< PANEL_HEIGHT, DE height (VOP_07[11:0], = Vend = VStart + Height - 1)

    // DClk related
    0,  //MS_U16 m_wPanelMaxHTotal;                ///<  PANEL_MAX_HTOTAL. Reserved for future using.
    (HDA+HPW+HBP+HFP),  //MS_U16 m_wPanelHTotal;                   ///<  VOP_0C[11:0], PANEL_HTOTAL
    0,  //MS_U16 m_wPanelMinHTotal;                ///<  PANEL_MIN_HTOTAL. Reserved for future using.

    0,  //MS_U16 m_wPanelMaxVTotal;                ///<  PANEL_MAX_VTOTAL. Reserved for future using.
    (VDA+VPW+VBP+VFP),  //MS_U16 m_wPanelVTotal;                   ///<  VOP_0D[11:0], PANEL_VTOTAL
    0,  //MS_U16 m_wPanelMinVTotal;                ///<  PANEL_MIN_VTOTAL. Reserved for future using.

    0,  //MS_U8 m_dwPanelMaxDCLK;                  ///<  PANEL_MAX_DCLK. Reserved for future using.
    ((unsigned long)(VDA+VPW+VBP+VFP)*(HDA+HPW+HBP+HFP)*FPS/1048576),  //MS_U8 m_dwPanelDCLK;                     ///<  LPLL_0F[23:0], PANEL_DCLK          ,{0x3100_10[7:0], 0x3100_0F[15:0]}
    0,  //MS_U8 m_dwPanelMinDCLK;                  ///<  PANEL_MIN_DCLK. Reserved for future using.
                                             ///<  spread spectrum
    0,  //MS_U16 m_wSpreadSpectrumStep;            ///<  move to board define, no use now.
    0,  //MS_U16 m_wSpreadSpectrumSpan;            ///<  move to board define, no use now.

    160,  //MS_U8 m_ucDimmingCtl;                    ///<  Initial Dimming Value
    255,  //MS_U8 m_ucMaxPWMVal;                     ///<  Max Dimming Value
    80,  //MS_U8 m_ucMinPWMVal;                     ///<  Min Dimming Value

    0,  //MS_U8 m_bPanelDeinterMode   :1;          ///<  define PANEL_DEINTER_MODE,  no use now
    E_MI_PNL_ASPECT_RATIO_WIDE,  //MHAL_DISP_PnlAspectRatio_e m_ucPanelAspectRatio; ///<  Panel Aspect Ratio, provide information to upper layer application for aspect ratio setting.
  /*
    *
    * Board related params
    *
    *  If a board ( like BD_MST064C_D01A_S ) swap LVDS TX polarity
    *    : This polarity swap value =
    *      (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L from board define,
    *  Otherwise
    *    : The value shall set to 0.
    */
    0,  //MS_U16 m_u16LVDSTxSwapValue;
    E_MI_PNL_TI_8BIT_MODE,  //MHAL_DISP_ApiPnlTiBitMode_e m_ucTiBitMode;                         ///< MOD_4B[1:0], refer to "LVDS output app note"
    E_MI_PNL_OUTPUT_8BIT_MODE,  //MHAL_DISP_ApiPnlOutPutFormatBitMode_e m_ucOutputFormatBitMode;

    0,  //MS_U8 m_bPanelSwapOdd_RG    :1;          ///<  define PANEL_SWAP_ODD_RG
    0,  //MS_U8 m_bPanelSwapEven_RG   :1;          ///<  define PANEL_SWAP_EVEN_RG
    0,  //MS_U8 m_bPanelSwapOdd_GB    :1;          ///<  define PANEL_SWAP_ODD_GB
    0,  //MS_U8 m_bPanelSwapEven_GB   :1;          ///<  define PANEL_SWAP_EVEN_GB

    /**
    *  Others
    */
    1,  //MS_U8 m_bPanelDoubleClk     :1;             ///<  LPLL_03[7], define Double Clock ,LVDS dual mode
    0x001c848e,  //MS_U32 m_dwPanelMaxSET;                     ///<  define PANEL_MAX_SET
    0x0018eb59,  //MS_U32 m_dwPanelMinSET;                     ///<  define PANEL_MIN_SET
    E_MI_PNL_CHG_VTOTAL,  //MHAL_DISP_ApiPnlOutTimingMode_e m_ucOutTimingMode;   ///<Define which panel output timing change mode is used to change VFreq for same panel
    0,  //MS_U8 m_bPanelNoiseDith     :1;             ///<  PAFRC mixed with noise dither disable
    (MI_PANEL_ChannelSwapType_e)2,
    (MI_PANEL_ChannelSwapType_e)4,
    (MI_PANEL_ChannelSwapType_e)3,
    (MI_PANEL_ChannelSwapType_e)1,
    (MI_PANEL_ChannelSwapType_e)0,
/*
    (MI_PANEL_ChannelSwapType_e)2,
    (MI_PANEL_ChannelSwapType_e)4,
    (MI_PANEL_ChannelSwapType_e)3,
    (MI_PANEL_ChannelSwapType_e)1,
    (MI_PANEL_ChannelSwapType_e)0,
*/
};

MI_U8 ST7703_720x1280[] =
{
 0xB9,3,0xF1,0x12,0x83,
 0xBA,27,0x33,0x81,0x05,0xF9,0x0E,0x0E,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x25,0x00,0x91,0x0A,0x00,0x00,0x02,0x4F,0xD1,0x00,0x00,0x37,
 0xB8,4,0x26,0x22,0x20,0x03,
 0xBF,3,0x02,0x11,0x00,       
 0xB3,10,0x0C,0x10,0x0A,0x50,0x03,0xFF,0x00,0x00,0x00,0x00,      
 0xC0,9,0x73,0x73,0x50,0x50,0x00,0x00,0x08,0x70,0x00,        
 0xBC,1,0x46,      
 0xCC,1,0x0B,       
 0xB4,1,0x80,        
 0xB2,3,0xC8,0x12,0x30,            
 0xE3,14,0x07,0x07,0x0B,0x0B,0x03,0x0B,0x00,0x00,0x00,0x00,0xFF,0x00,0x40,0x10,            
 0xC1,12,0x53,0x00,0x1E,0x1E,0x77,0xC1,0xFF,0xFF,0xAF,0xAF,0x7F,0x7F,   
 0xB5,2,0x07,0x07,        
 0xB6,2,0x81,0x81,        
 0xC6,6,0x00,0x00,0xFF,0xFF,0x01,0xFF,        
 0xE9,63,0XC2,0x10,0x05,0x04,0xFE,0x02,0xA1,0x12,0x31,0x45, \
         0x3F,0x83,0x12,0xB1,0x3B,0x2A,0x08,0x05,0x00,0x00, \
         0x00,0x00,0x08,0x05,0x00,0x00,0x00,0x00,0xFF,0x02, \
         0x46,0x02,0x48,0x68,0x88,0x88,0x88,0x80,0x88,0xFF, \
         0x13,0x57,0x13,0x58,0x78,0x88,0x88,0x88,0x81,0x88, \
         0x00,0x00,0x00,0x00,0x00,0x12,0xB1,0x3B,0x00,0x00, \
         0x00,0x00,0x00,
 0xEA,61,0x00,0x1A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
        0x00,0x00,0xFF,0x31,0x75,0x31,0x18,0x78,0x88,0x88,  \
        0x88,0x85,0x88,0xFF,0x20,0x64,0x20,0x08,0x68,0x88,  \
        0x88,0x88,0x84,0x88,0x20,0x10,0x00,0x00,0x54,0x00,  \
        0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x0C,  \
        0x00,0x00,0x00,0x00,0x30,0x02,0xA1,0x00,0x00,0x00,  \
        0x00,
 0xE0,34,0x00,0x00,0x00,0x17,0x39,0x3F,0x1C,0x15,0x00,0x05, \
        0x0B,0x0F,0x11,0x0F,0x12,0x0E,0x14,0x00,0x00,0x00,  \
        0x17,0x39,0x3F,0x1C,0x15,0x00,0x05,0x0B,0x0F,0x11,  \
        0x0F,0x12,0x0E,0x14,  
 0x11,1,0x00,

 FLAG_DELAY,FLAG_DELAY,150,
 0x29,1,0x00,
 FLAG_DELAY,FLAG_DELAY,50,
 
 
 FLAG_END_OF_TABLE, FLAG_END_OF_TABLE,
};

MI_PANEL_MipiDsiConfig_t stMipiDsiConfig =
{
    //HsTrail HsPrpr HsZero ClkHsPrpr ClkHsExit ClkTrail ClkZero ClkHsPost DaHsExit ContDet
    3,        3,       4,     2,          5,       3,       9,     9,       5,       0,
    //Lpx   TaGet  TaSure  TaGo
    16,     26,    24,     50,

    //Hac,  Hpw,  Hbp, Hfp, Vac,  Vpw,  Vbp, Vfp,  Bllp, Fps
      HDA,  HPW,  HBP, HFP, VDA, VPW,  VBP, VFP,  0,    FPS,

    E_MI_PNL_MIPI_DSI_LANE_4,      // MIPnlMipiDsiLaneMode_e enLaneNum;
    E_MI_PNL_MIPI_DSI_RGB888,      // MIPnlMipiDsiFormat_e enFormat;
    E_MI_PNL_MIPI_DSI_SYNC_PULSE,  // MIPnlMipiDsiCtrlMode_e enCtrl;

    ST7703_720x1280,
    sizeof(ST7703_720x1280),
    1, 0x01AF, 0x01B9, 0x80D2, 7,
};
