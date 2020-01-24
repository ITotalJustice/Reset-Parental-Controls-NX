#include <stdio.h>
#include <switch.h>


void init_app(void)
{
    consoleInit(NULL);
    pctlInitialize();
}

void exit_app(void)
{
    consoleExit(NULL);
    pctlExit();
}

void print_display(const char *message)
{
    printf(message);
    consoleUpdate(NULL);
}

int main(int argc, char *argv[])
{
    init_app();

    print_display("Reset Parental Controls: Reseting the pin made easy!\n\n\n\n");

    print_display("Press (A) to set parental control pin\n\n");
    print_display("Press (B) to exit\n\n");

    while (appletMainLoop())
    {
        hidScanInput();
        uint64_t k = hidKeysDown(CONTROLLER_P1_AUTO);

        if (k & KEY_A)
        {
            if (R_FAILED(pctlauthRegisterPasscode()))
            {
                print_display("Failed to launch pctl change passcode\n\n");
            }
            else
            {
                print_display("\n\n\n\nParental control pin succesfully set!\n\n\n\n");
                print_display("### To remove parental controls, please follow the steps below: ###\n\n");
                print_display("System settings -> Parental Controls -> Change settings (enter pin).\n\n");
                print_display("From there press (X) to remove parental controls\n\n");
            }
        }

        if (k & KEY_B)
        {
            break;
        }
    }

    exit_app();
    return 0;
}