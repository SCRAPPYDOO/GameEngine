#ifndef _FEAT_DEF_H_
    #define _FEAT_DEF_H_

#define HeroicFeatsBegin 1000
#define HeroicFeatsEnd 1086

enum FeatType
{
	/* Players HandBook */

	//Heroic Tier Feats
	FeatActionSurge = 1000, 
	FeatAgileHunter,
	FeatAlertness,
	FeatArmorOfBahamut,
	FeatArmorProficiencyChainmail,
	FeatArmorProficiencyLeather, 
	FeatArmorProficiencyHide,
	FeatArmorProficiencyPlate,
	FeatArmorProficiencyScale,
	FeatAstralFire, 
	FeatAvandrasRescue, 
	FeatBackstabber,
	FeatBladeOpportunist,
	FeatBurningBlizzard, 
	FeatCombatReflexes,
	FeatCorellonsGrace, 
	FeatDarkFury,
	FeatDefensiveMobility,
	FeatDistractingShield, 
	FeatDodgeGiants, 
	FeatDragonbornFrenzy, 
	FeatDragonbornSenses, 
	FeatDurable,
	FeatDwarvenWeaponTraining,
	FeatEladrinSoldier, 
	FeatElvenPrecision, 
	FeatEnlargedDragonBreath,
	FeatEscapeArtist, 
	FeatExpandedSpellbook, 
	FeatFarShot, 
	FeatFarThrow, 
	FeatFastRunner, 
	FeatFerociousRebuke, 
	FeatGroupInsight, 
	FeatHalflingAgility, 
	FeatHarmonyOfErathis, 
	FeatHealingHands,
	FeatHellfireBlood, 
	FeatHumanPerseverance, 
	FeatImprovedDarkOnesBlessing, 
	FeatImprovedFateOfTheVoid,
	FeatImprovedInitiative, 
	FeatImprovedMistyStep,
	FeatInspiredRecovery,
	FeatInspiringPresence,
	FeatIounsPoise, 
	FeatJackOfAllTrades,
	FeatKordsFavor, 
	FeatLethalHunter,
	FeatHuntersQuarry,
	FeatLightStep,
	FeatStealth,
	FeatLinguist, 
	FeatLongJumper, 
	FeatLostInTheCrowd, 
	FeatMelorasTide, 
	FeatMoradinsResolve, 
	FeatMountedCombat,
	FeatNimbleBlade,
	FeatPelorsRadiance, 
	FeatPotentChallenge, 
	FeatCombatChallenge, 
	FeatPowerAttack, 
	FeatPowerfulCharge, 
	FeatPreciseHunter, 
	FeatPressTheAdvantage,
	FeatQuickDraw, 
	FeatRagingStorm, 
	FeatRavenQueensBlessing, 
	FeatRitualCaster, 
	FeatSehaninesReversal, 
	FeatShieldProficiencyHeavy,
	FeatShieldProficiencyLight,
	FeatShieldPush,
	FeatSkillFocus, 
	FeatSkillTraining,
	FeatSureClimber, 
	FeatSurpriseKnockdown, 
	FeatTacticalAssault,
	FeatTacticalPresence, 
	FeatToughness, 
	FeatTwoWeaponDefense, 
	FeatTwoWeaponFighting, 
	FeatWeaponFocus,
	FeatWeaponProficiency, 
	FeatWintertouched,

	//Class Feats Cleric
	ChannelDivinity, 
	HealersLore, 
	HealingWord, 
	RitualCasting,


////Paragon Tier Feats
//Action Recovery Human Gain extra saving throws by spending action point
//Agile Athlete — Roll twice with Acrobatics and Athletics checks
//Arcane Reach Dex 15 Choose square within 2 as origin with close attack power
//Armor Specialization Dex 15, training with chainmail +1 to AC with chainmail, reduce check penalty by 1
//(Chainmail)
//Armor Specialization (Hide) Con 15, training with hide armor +1 to AC with hide armor, reduce check penalty by 1
//Armor Specialization (Plate) Con 15, training with plate armor +1 to AC with plate armor
//Armor Specialization (Scale) Dex 15, training with scale armor Ignore speed penalty of scale armor
//Back to the Wall — +1 to melee attack, damage, AC when adjacent to a wall
//Blood Thirst — +2 to damage against bloodied foes
//Combat Anticipation — +1 to defenses against ranged, area, close attacks
//Combat Commander Warlord, Bonus to Combat Leader equals Cha or Int modifier
//Combat Leader class feature
//Danger Sense — Roll twice for initiative, use the higher result
//Deadly Axe Str 17, Con 13 Treat all axes as high crit weapons
//Defensive Advantage Dex 17 +2 AC when you have combat advantage against enemy
//Devastating Critical — Deal additional 1d10 damage on a critical hit
//Distant Shot — Ignore –2 penalty for long range
//Dwarven Durability Dwarf Increase number of healing surges, healing surge value
//Empowered Dragon Breath Dragonborn, Dragon breath uses d10s
//dragon breath racial power
//Evasion Dex 15 No damage from missed area or close attack
//Feywild Protection Eladrin, fey step racial power +2 to defenses when you use fey step
//Fiery Rebuke Tiefling, Cause fire damage with infernal wrath
//infernal wrath racial power
//Fleet-Footed — +1 to speed
//Great Fortitude — +2 to Fortitude defense
//Hammer Rhythm Str 15, Con 17 Damage with hammer or mace on a miss
//Heavy Blade Opportunity Str 15, Dex 15 Use at-will power with opportunity attack
//Improved Second Wind — Heal 5 additional damage with second wind
//Inescapable Force — Force powers ignore insubstantial, deal additional
//damage
//
//Iron Will — +2 to Will defense
//Lasting Frost — Target hit with cold power gains vulnerable cold 5
//Light Blade Precision Dex 13, Small or Medium size +2 damage against Large or larger targets
//Lightning Arc — Affect second target with lightning power on critical hit
//Lightning Reflexes — +2 to Reflex defense
//Mettle — No damage from missed area or close attacks
//Point-Blank Shot — Ignore cover and concealment within 5 squares
//Polearm Gamble Str 15, Wis 15 Make opportunity attack against adjacent enemy
//Psychic Lock — Target hit with psychic power takes –2 on
//next attack roll
//Resounding Thunder — Add 1 to size of blast or burst with thunder keyword
//Running Shot Elf No attack penalty to ranged attacks after you run
//Scimitar Dance Str 15, Dex 17 Deal Dex modifier damage on miss
//Second Implement Wizard, Arcane Implement Gain mastery with second arcane implement
//Mastery class feature
//Secret Stride Trained in Stealth No penalty to Stealth with move while hiding or sneaking
//Seize the Moment Dex 17 Gain combat advantage over foe with lower initiative
//Shield Specialization Dex 15, Shield +1 to AC and Reflex when using a shield
//Proficiency (Heavy or Light)
//Sly Hunter Wis 15 +3 damage with bow against isolated target
//Solid Sound Con 13 +2 to defense after you use thunder or force power
//Spear Push Str 15, Dex 13 Add 1 square to distance pushed with spear or polearm
//Spell Focus Cha 13, wizard –2 to saves against your wizard spells
//Steady Shooter Con 15 +3 damage with crossbow if you don’t move
//Sweeping Flail Str 15, Dex 15 +2 to attacks with flail against foe with a shield
//Twofold Curse Warlock, Curse the two nearest enemies
//Warlock’s Curse class feature
//Uncanny Dodge Wis 15 Enemies denied bonus to attack from
//combat advantage
//Underfoot Halfling, trained in Acrobatics Move through spaces of Large or larger creatures
//
////Epic Tier Feats
//Arcane Mastery Wizard Regain daily spell by spending action point
//Axe Mastery Str 21, Con 17 Critical hit with axe melee attack roll of 19 or 20
//Blind-Fight Wis 13 or trained in Perception Adjacent creatures aren’t concealed or invisible to you
//Bludgeon Mastery Str 19, Con 19 Critical hit with bludgeoning melee attack roll of 19 or 20
//Epic Resurgence — Regain encounter attack power on critical hit
//Flail Mastery Str 19, Dex 19 Critical hit with flail melee attack roll of 19 or 20
//Flanking Maneuver Dex 17, trained in Acrobatics Move diagonally and through enemies’ spaces
//Font of Radiance — Target illuminated with critical hit, takes radiant damage
//Heavy Blade Mastery Str 21, Dex 17 Critical hit with heavy blade melee attack roll of 19 or 20
//Irresistible Flame — Decrease target’s resist fire by 20
//Light Blade Mastery Str 17, Dex 21 Critical hit with light blade melee attack roll of 19 or 20
//Pick Mastery Str 21, Con 17 Critical hit with pick melee attack roll of 19 or 20
//Spear Mastery Str 19, Dex 19 Critical hit with spear melee attack roll of 19 or 20
//Spell Accuracy Wizard Omit squares from any area or close wizard power
//Triumphant Attack — Target at –2 to attacks and defenses after a critical hit
//Two-Weapon Flurry Dex 19, Two-Weapon Fighting Make opportunity attack with off-hand melee weapon
//Unfettered Stride Trained in Acrobatics Ignore the effect of difficult terrain on your movement
//
////MultiClass Feats
//Initiate of the Faith Wis 13 Cleric: Religion skill, healing word 1/day
//Student of the Sword Str 13 Fighter: skill training, +1 to attack and mark 1/encounter
//Soldier of the Faith Str 13, Cha 13 Paladin: skill training, divine challenge 1/encounter
//Warrior of the Wild Str 13 or Dex 13 Ranger: skill training, designate prey 1/encounter
//Sneak of Shadows Dex 13 Rogue: Thievery skill, Sneak Attack 1/encounter
//Pact Initiate Cha 13 Warlock: skill training, eldritch blast 1/encounter
//Student of Battle Str 13 Warlord: skill training, inspiring word 1/day
//Arcane Initiate Int 13 Wizard: Arcana skill, wizard power 1/encounter
//Novice Power Any class-specific multiclass Swap one encounter power with one of multiclass
//feats, 4th level
//Acolyte Power Any class-specific multiclass Swap one utility power with one of multiclass
//feats, 8th level
//Adept Power

	/* End Of Players HandBook */
		
	//End Of Feats
	FeatMax,
};

static std::string FeatName[HeroicFeatsEnd - 1] =
{
	"Action Surge",
	"Agile Hunter",
	"Alertness",
	"Armor Of Bahamut",
};

#endif

