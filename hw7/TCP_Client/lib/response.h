#include <stdio.h>

void outputResponse(int responseCode){
    switch (responseCode)
        {
            case 100:
                printf("RESPONSE CODE: %d : Connection success\n",responseCode);
                break;

            // Login request
            case 110:
                printf("RESPONSE CODE: %d : Log in successfully\n",responseCode);
                break;
            
            case 211:
                printf("RESPONSE CODE: %d : Your account has been banned\n",responseCode);
                break;
            
            case 212:
                printf("RESPONSE CODE: %d : Your account does not exist\n",responseCode);
                break;
            
            case 213:
                printf("RESPONSE CODE: %d : Your account has been login on another client\n",responseCode);
                break;

            case 214:
                printf("RESPONSE CODE: %d : You have already login\n",responseCode);
                break;
            // Post request
            case 120:
                printf("RESPONSE CODE: %d : Posting successfully\n",responseCode);
                break; 
            // Logout request
            case 130:
                printf("RESPONSE CODE: %d : Log out successfully\n",responseCode);
                break;
            // Error    
            case 221:
                printf("RESPONSE CODE: %d : You have not login yet. Please login to take actions\n",responseCode);
                break;
            
            case 300:
                printf("RESPONSE CODE: %d : UNDEFINED REQUEST\n",responseCode);
                break;
            case 400:
                printf("RESPONSE CODE: %d : UNDEFINED ERROR\n",responseCode);
                break;
            case 500:
                printf("RESPONSE CODE: %d : INTERNAL SERVER ERROR\n",responseCode);
                break;
            default:
                break;
        }
}