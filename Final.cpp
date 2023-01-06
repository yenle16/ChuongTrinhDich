#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <cstring>
#include <string.h>

const int ERROR_STATE = 999;

const int KHONG_DOAN_NHAN = 1000;
typedef int state;
typedef char *attri;
typedef char *token;

// ham tra ve ky tu tiep theo
unsigned char readchar(const char *x, unsigned int i)
{
    if (i < strlen(x))
        return (*(x + i));
    else
        return ('\0');
}

// ham tra ve thuoc tinh tuong ung voi trang thai ket thuc
attri atrribute(state s)
{
    char tmp[256];
    char *ch = tmp;
    switch (s)
    {
    case 2:
        strcpy(ch, "so sanh lon hon bang");
        break;
    case 3:
        strcpy(ch, "dich phai");
        break;
    case 4:
        strcpy(ch, "so sanh lon hon");
        break;
    case 6:
        strcpy(ch, "so sanh nho hon bang");
        break;
    case 7:
        strcpy(ch, "dich trai");
        break;
    case 8:
        strcpy(ch, "so sanh nho hon");
        break;
    case 10:
        strcpy(ch, "so sanh khong bang");
        break;
    case 11:
        strcpy(ch, "phu dinh");
        break;
    case 13:
        strcpy(ch, "so sanh bang");
        break;
    case 14:
        strcpy(ch, "gan");
        break;
    case 17:
        strcpy(ch, "cong bang");
        break;
    case 18:
        strcpy(ch, "tang 1");
        break;
    case 19:
        strcpy(ch, "cong");
        break;
    case 21:
        strcpy(ch, "tru bang");
        break;
    case 22:
        strcpy(ch, "giam 1");
        break;
    case 23:
        strcpy(ch, "tru");
        break;
    case 25:
        strcpy(ch, "nhan bang");
        break;
    case 26:
        strcpy(ch, "nhan");
        break;
    case 28:
        strcpy(ch, "chia bang");
        break;
    case 29:
        strcpy(ch, "chia");
        break;
    case 30:
        strcpy(ch, "chia lay du");
        break;

    case 35:
        strcpy(ch, "so thuc");
        break;
    case 36:
        strcpy(ch, "so nguyen thap phan");
        break;
    case 37:
        strcpy(ch, "LOI: ten ko bat dau bang so hoac cac ki tu dac biet");
        break;
    case 39:
        strcpy(ch, "so nguyen he bat phan");
        break;
    case 41:
        strcpy(ch, "so nguyen he thap luc phan");
        break;
    case 42:
        strcpy(ch, "LOI: so nguyen he thap luc phan khong co chu g=>z");
        break;
    case 43:
        strcpy(ch, "so nguyen 0");
        break;
    case 45:
        strcpy(ch, "LOI: bat phan ko co so 8,9");
        break;

    case 49:
        strcpy(ch, "ten bien, ham, tu khoa, hang");
        break;
    case 52:
        strcpy(ch, "and");
        break;
    case 53:
        strcpy(ch, "and bit roi gan");
        break;
    case 54:
        strcpy(ch, "and nhi phan");
        break;
    case 56:
        strcpy(ch, "or");
        break;
    case 57:
        strcpy(ch, "or bit roi gan");
        break;
    case 58:
        strcpy(ch, "or nhi phan");
        break;
    case 60:
        strcpy(ch, "hoac loai tru bit roi gan");
        break;
    case 61:
        strcpy(ch, "xor nhi phan");
        break;
    case 62:
        strcpy(ch, "phu dinh tren bit");
        break;
    case 63:
        strcpy(ch, "chu thich mot dong");
        break;
    case 64:
        strcpy(ch, "chu thich mot dong");
        break;
//    case 65:
//        strcpy(ch, "chu thich nhieu dong");
//        break;
    case 67:
        strcpy(ch, "chu thich nhieu dong");
        break;
    default:
        strcpy(ch, "token khong duoc du doan \0");
    }
    return (attri)ch;
}

// ham kiem tra s co phai la trang thai ket thuc khong sao?
int nostar_end_state(state s)
{
    switch (s)
    {
    case 2:
    case 3:
    case 6:
    case 7:
    case 10:
    case 13:
    case 17:
    case 18:
    case 21:
    case 22:
    case 25:
    case 28:

    case 37:
    case 41:
    case 42:

    case 64:
    case 67:

    case 52:
    case 53:
    case 56:
    case 57:
    case 60:
    case 62:
    case 30:
        return 1;
    default:
        return 0;
    }
}

// ham kiem tra trang thai s co phai la trang thai ket thuc co sao?
int star_end_state(state s)
{
    switch (s)
    {
    case 4:
    case 8:
    case 11:
    case 14:
    case 19:
    case 23:
    case 26:

    case 35:
    case 36:
    case 39:
    case 41:
    case 43:
    case 45:

    case 49:

    case 54:
    case 58:
    case 61:
    case 29:
        return 1;
    default:
        return 0;
    }
}

// ham kiem tra chuyen nhanh
state start_state_otherbrand(state s)
{
    state start;
    switch (s)
    {
    case 0:
        start = 15;
        break;
    case 15:
        start = 31;
        break;
    case 31:
        start = 47;
        break;
    case 47:
        start = 50;
        break;
    case 50:
        start = ERROR_STATE;
    }
    return start;
}

// ham kiem tra trang thai bat dau
int start_state(state s)
{
    if ((s == 0) || (s == 15) || s == 31 || s == 47 || s == 50)
        return 1;
    return 0;
}

// ham ghep them ky tu c vao tu to tk
void catchar_in_token(unsigned char c, char *tk)
{
    *(tk + (strlen(tk) + 1)) = '\0';
    *(tk + strlen(tk)) = c;
}

// ham tim kiem tu khoa theo phuong phap mo phong
void search_token(const char *x, unsigned int &i, attri tt, token tk)
{
    state s = 0;
    int stop = 0;
    unsigned char c;

    while (i <= strlen(x) && (!stop))
    {

        c = readchar(x, i);
        switch (s)
        {
        case 0:
            if (c == '>')
                s = 1;
            else if (c == '<')
                s = 5;
            else if (c == '!')
                s = 9;
            else if (c == '=')
                s = 12;
            else
                s = start_state_otherbrand(s);
            break;
        case 1:
            if (c == '=')
                s = 2;
            else if (c == '>')
                s = 3;
            else
                s = 4;
            break;

        case 5:
            if (c == '=')
                s = 6;
            else if (c == '<')
                s = 7;
            else
                s = 8;
            break;

        case 9:
            if (c == '=')
                s = 10;
            else
                s = 11;
            break;

        case 12:
            if (c == '=')
                s = 13;
            else
                s = 14;
            break;

        case 15:
            if (c == '+')
                s = 16;
            else if (c == '-')
                s = 20;
            else if (c == '*')
                s = 24;
            else if (c == '/')
                s = 27;
            else if (c == '%')
                s = 30;
            else
                s = start_state_otherbrand(s);
            break;

        case 16:
            if (c == '=')
                s = 17;
            else if (c == '+')
                s = 18;
            else
                s = 19;
            break;

        case 20:
            if (c == '=')
                s = 21;
            else if (c == '-')
                s = 22;
            else
                s = 23;
            break;

        case 24:
            if (c == '=')
                s = 25;
            else
                s = 26;
            break;

        case 27:
            if (c == '=')
                s = 28;
            else if (c == '/')
                s = 63;
            else if (c == '*')
                s = 65;
            else
                s = 29;
            break;

        case 63:
            if (c == '\n')
                s = 64;
            else
                s = 63;
            break;
        case 65:
            if (c == '*')
                s = 66;
            else
                s = 65;
            break;
        case 66:
            if (c == '/')
                s = 67;
            else
                s = 65;
            break;
        case 31:

            if (c >= '1' && c <= '9')
                s = 33;
            else if (c == '.')
                s = 32;

            else if (c == '0')
                s = 34;
            else
                s = start_state_otherbrand(s);
            break;
        case 32:
            if (c >= '0' && c <= '9')
                s = 46;
            else
                s = 37;
            break;
        case 33:
            if (c >= '0' && c <= '9')
                s = 33;
            else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
                s = 37;
            else if (c == '.')
                s = 32;
            else
                s = 36;
            break;
        case 34:
            if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) && (c != 'x' && c != 'X'))
                s = 37;
            else if (c >= '0' && c <= '7')
                s = 38;
            else if (c == 'x' || c == 'X')
                s = 40;
            else if (c == '8' || c == '9')
                s = 44;
            else if (c == '.')
            {
                s = 32;
            }

            else
                s = 43;
            break;
        case 38:
            if (c >= '0' && c <= '7')
                s = 38;
            else
                s = 39;
            break;
        case 40:
            if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))
                s = 40;
            else if ((c >= 'g' && c <= 'z') || (c >= 'G' && c <= 'Z'))
                s = 42;
            else
                s = 41;
            break;
        case 44:
            if (c >= '0' && c <= '9')
                s = 44;
            else if (c == '.')
                s = 32;
            else
                s = 45;
            break;
        case 46:
            if (c >= '0' && c <= '9')
                s = 46;
            else
                s = 35;
            break;
        //
        case 47:
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
                s = 48;
            else
                s = start_state_otherbrand(s);
            break;
        case 48:
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' || (c >= '0' && c <= '9'))
                s = 48;
            else
                s = 49;
            break;
        //
        case 50:
            if (c == '&')
                s = 51;
            else if (c == '|')
                s = 55;
            else if (c == '^')
                s = 59;
            else if (c == '~')
                s = 62;
            else
                s = start_state_otherbrand(s);
            break;
        case 51:
            if (c == '&')
                s = 52;
            else if (c == '=')
                s = 53;
            else
                s = 54;
            break;
        case 55:
            if (c == '|')
                s = 56;
            else if (c == '=')
                s = 57;
            else
                s = 58;
            break;
        case 59:
            if (c == '=')
                s = 60;
            else
                s = 61;
            break;
        default:
            stop = 1;
            break;
        }
        if (s == ERROR_STATE)
        {
            stop = 1;
            if (c != ' ')
            {
                catchar_in_token(c, tk);
                strcpy(tt, atrribute(KHONG_DOAN_NHAN));
            }
            else
            {
                *tk = '\0';
                *tt = '\0';
            }
            i++;
        }
        else if (start_state(s))
            ; // bđ
        else if (nostar_end_state(s))
        { // trang thai ket thuc ko sao
            catchar_in_token(c, tk);
            i = i + 1; // tiep
            stop = 1;
            // strcpy(tt,atrribute(s));
        }
        else if (star_end_state(s))
        {
            // strcpy(tt,atrribute(s));    // ket thuc co sao
            stop = 1;
            // i++;
        }
        else
        {
            catchar_in_token(c, tk);
            i = i + 1;
            // c = readchar(x,i);
        }
    }
    strcpy(tt, atrribute(s));
}

// ham luu tk va a vao danh sach
void save_token_and_attribute(token tk, attri a)
{
    if (*tk != '\0')
    {
    for (int i = 0; i < strlen(tk); i++)
        printf("%c", *(tk + i));
    printf("      ");
    for (int i = 0; i < strlen(a); i++)
        printf("%c", *(a + i));
    printf("\n");
    }
}

// bo phan tich tu vung
void lexical_analysis(char *x)
{
    char ml[256];
    char m[256];
    token tk = ml;
    attri a = m;
    unsigned int i = 0;
    do
    {
        *tk = '\0';
        *a = '\0';
        search_token(x, i, a, tk);
        save_token_and_attribute(tk, a);
    } while ((i < strlen(x)));
}

int main()
{
    
    char z[256];
    char *x = z;
	
    while (true)
    {
        printf("\nNhap xau x: ");
        gets(x);
        lexical_analysis(x);
	}
    
    return 0;
}
