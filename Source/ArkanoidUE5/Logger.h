#pragma once

#define print(Text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, TEXT(Text), false) 
#define print_k(Key, Text) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.f, FColor::White, TEXT(Text)) 

#define printf(Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::White, FString::Printf(TEXT(Format), ##__VA_ARGS__ ), false)
#define printf_k(Key, Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.f, FColor::White, FString::Printf(TEXT(Format), ##__VA_ARGS__ ))

#define warn(Text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, TEXT(Text), false) 
#define warn_k(Key, Text) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.f, FColor::Yellow, TEXT(Text)) 
//#define warnf Format ... if (GEngine) GEngine- ddOnScreenDebugMessagei -1 2.f FColor::Yellow FStrin ::Printf TEXT(Format), ##__VA_ARGS__ ) ,false)
#define warnf_k(Key, Format, ...) if (GEngine) GEngine->AddOnScreenDebugMessage(Key, 2.f, FColor::Yellow, FString::Printf(TEXT(Format), ##__VA_ARGS__))  

#define printc(Text, Color) if (GEngine) GEngine->AddOnScreenDebugMessage( -1, 2.f, Color, TEXT(Text), false) 