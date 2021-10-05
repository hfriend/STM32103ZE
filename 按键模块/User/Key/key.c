#include "key.h"

static uint8_t Key_Sta[4][4] = { {1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1} };

void Key_GPIOF_Init(void)
{
	GPIO_InitTypeDef GPIOF_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
	//PF4-PF7��Ϊ�������ţ���������
	GPIOF_InitStructure.GPIO_Pin	 = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIOF_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
	GPIO_Init(GPIOF, &GPIOF_InitStructure);
	
	GPIOF_InitStructure.GPIO_Pin	 = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIOF_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIOF_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIOF_InitStructure);
	
}	
	
/*
	������ƽ״̬��ɨ�裨�߻�ͣ�
	ͨ��ɨ��8������λ�ķ���������������
	��TIM6==5msһ���жϣ���ôһ�������ж���Ҫ16���жϣ�Ҳ����80ms���һ���ж�
	�˷�Ӧ���200ms
*/
void KeyScan(void)
{
	static uint8_t Key_Buff[4][4] = { {0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF},{0xFF,0xFF,0xFF,0xFF} };
	static uint8_t keyout = 0;
	uint8_t i;
		
	//һ���Լ��ͬһ�е��ĸ�����ֵ
	Key_Buff[keyout][0] = (Key_Buff[keyout][0] << 1 ) | KEY_IN_1;
	Key_Buff[keyout][1] = (Key_Buff[keyout][1] << 1 ) | KEY_IN_2;
	Key_Buff[keyout][2] = (Key_Buff[keyout][2] << 1 ) | KEY_IN_3;
	Key_Buff[keyout][3] = (Key_Buff[keyout][3] << 1 ) | KEY_IN_4;
 
	//������İ�������ж�
	for(i=0;i<4;i++)
		{
				if( (Key_Buff[keyout][i] & 0x0F) == 0x00)	//���������ĸ�ֵ����0������ж�����
						Key_Sta[keyout][i] = 0;
				if( (Key_Buff[keyout][i] & 0x0F) == 0x0F)
						Key_Sta[keyout][i] = 1;
		}
		
	keyout++;
	keyout = keyout&0x03; // keyout�ķ�Χ��0~3��������0

	switch(keyout)
	{
		case 0 : KEY_OUT_1 = 0,KEY_OUT_2 = 1,KEY_OUT_3 = 1,KEY_OUT_4 = 1; break; 
		case 1 : KEY_OUT_1 = 1,KEY_OUT_2 = 0,KEY_OUT_3 = 1,KEY_OUT_4 = 1; break; 
		case 2 : KEY_OUT_1 = 1,KEY_OUT_2 = 1,KEY_OUT_3 = 0,KEY_OUT_4 = 1; break; 
		case 3 : KEY_OUT_1 = 1,KEY_OUT_2 = 1,KEY_OUT_3 = 1,KEY_OUT_4 = 0; break; 
		default:break;
	}
	
}

/*�����ĵ����⣨���µļ���*/
void KeyDriver(void)
{
	//����ֵ�ı��ݣ�����Ϊ1������Ϊ0��������ʵ�ʰ���ֵ�Ƚ�
	static uint8_t Key_Backup[4][4] = { {1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1} };
	uint8_t row,column;
	for(row = 0 ; row < 4 ; row++ )
		{
			for(column = 0 ; column <4 ;column++)
			{
				if(Key_Sta[row][column] != Key_Backup[row][column]) //˵������ֵ�б仯
				{
					if(Key_Backup[row][column] != 0) //������0�Ļ���˵��Key_Scan��һ��״̬�ǵ���״̬
					{
						//���KeyScan�������Ļ����˿ڴ������1
						//printf("1");
						KeyAction( row*4+column );
					}
					Key_Backup[row][column] = Key_Sta[row][column] ; //����ֵ����
				}
			}
		}
	
}

/*���ݰ���ֵ����ִ�ж�Ӧ�Ĳ���*/
void KeyAction(uint8_t Key_Value)
{
	switch(Key_Value)
	{
		case 0 : printf("0") ;break;
		case 1 : printf("1") ;break;
		case 2 : printf("2") ;break;
		case 3 : printf("3") ;break;
		case 4 : printf("4") ;break;
		case 5 : printf("5") ;break;
		case 6 : printf("6") ;break;
		case 7 : printf("7") ;break;
		case 8 : printf("8") ;break;
		case 9 : printf("9") ;break;
		case 10: printf("10") ;break;
		case 11: printf("11") ;break;
		case 12: printf("12") ;break;
		case 13: printf("13") ;break;
		case 14: printf("14") ;break;
		case 15: printf("15") ;break;
		default:break;
	}
}

