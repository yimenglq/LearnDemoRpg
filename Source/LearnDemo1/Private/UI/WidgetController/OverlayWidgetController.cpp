// Fill out your copyright notice in the Description page of Project Settings.

#include"AbilitySystem/AuraAttributeSet.h"
#include"AbilitySystem/AuraAbilitySystemComponent.h"
#include "UI/WidgetController/OverlayWidgetController.h"



void UOverlayWidgetController::Broadcast() const
{
	OnHealthChanged.Broadcast(OwnerAuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(OwnerAuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(OwnerAuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(OwnerAuraAttributeSet->GetMaxMana());

}

void UOverlayWidgetController::BindDelegateSignatureI_MULTICAST()
{
	//�� UAuraAttributeSet ���Լ��� ��Ա���� FGameplayAttributeData Health; ����ʱ �����Ļص�����
	OwnerAuraAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(OwnerAuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::OnHealthAttribute);
	OwnerAuraAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(OwnerAuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::OnMaxHealthAttribute);
	OwnerAuraAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(OwnerAuraAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::OnManaAttribute);
	OwnerAuraAbilitySystemComp->GetGameplayAttributeValueChangeDelegate(OwnerAuraAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::OnMaxManaAttribute);

	OwnerAuraAbilitySystemComp->OnEffectTagsSignature.AddLambda(
		[this](FGameplayTagContainer& TagContainer)
		{
			for (const FGameplayTag& tag : TagContainer)
			{
				// * ��ȡ�� TagName ��Ӧ�� FGameplayTag
				FGameplayTag Tag1 = FGameplayTag::RequestGameplayTag(TEXT("Message") );
				//�ȶԱ�ǩ �� tag = Message.da    Tag1 = Message    tag.MatchesTag(Tag1) return true;
				//tag = Message    Tag1 = Message.a    tag.MatchesTag(Tag1) return false;
				if (tag.MatchesTag(Tag1))
				{
					
					
					FUIWidgetRow* widgetRow = 	GetMessgaeRow<FUIWidgetRow>(tag.GetTagName());
					OnMessageWidgetRowSignature.Broadcast(*widgetRow);

				}

			
			}

			

		}
	);

}

void UOverlayWidgetController::OnHealthAttribute(const FOnAttributeChangeData& Data)
{
	//ί�зַ�
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnMaxHealthAttribute(const FOnAttributeChangeData& Data)
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnManaAttribute(const FOnAttributeChangeData& Data)
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::OnMaxManaAttribute(const FOnAttributeChangeData& Data)
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
