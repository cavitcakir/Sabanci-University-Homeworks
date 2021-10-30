/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

#include "xsi.h"

struct XSI_INFO xsi_info;



int main(int argc, char **argv)
{
    xsi_init_design(argc, argv);
    xsi_register_info(&xsi_info);

    xsi_register_min_prec_unit(-12);
    work_m_00000000003672060749_4196211228_init();
    work_m_00000000002982712009_3598138731_init();
    work_m_00000000000507942055_0505561268_init();
    work_m_00000000002690563388_2367730945_init();
    work_m_00000000001767739061_3835325501_init();
    work_m_00000000003196318225_0440198948_init();
    work_m_00000000001439308953_1181546379_init();
    work_m_00000000003784393713_0804624270_init();
    work_m_00000000004134447467_2073120511_init();


    xsi_register_tops("work_m_00000000003784393713_0804624270");
    xsi_register_tops("work_m_00000000004134447467_2073120511");


    return xsi_run_simulation(argc, argv);

}
