#include <GDMake.h>
#include <string>
        
uintptr_t base = (uintptr_t)GetModuleHandleA(0);

namespace MoreOptionsLayer {
    inline int(__thiscall* addToggle)(cocos2d::CCLayer* self, const char* display, const char* key, const char* extraInfo);
}

GDMAKE_HOOK(0x1DE8F0)
bool __fastcall MoreOptionsLayer_initHook(cocos2d::CCLayer* self) {
    if (!GDMAKE_ORIG(self))
        return false;

    MoreOptionsLayer::addToggle(
        self,
        "Disable Menu Animation",
        "8001",
        nullptr
    );

    return true;
}

GDMAKE_HOOK(MenuLayer::init)
bool __fastcall initHook(gd::MenuLayer* _self) {
    if (!GDMAKE_ORIG(_self))
        return false;

    if (gd::GameManager::sharedState()->getGameVariable("8001"))
        return true;

    cocos2d::CCArray* c = _self->getChildren();

    {   // main buttons
        cocos2d::CCArray* c2 = ((cocos2d::CCNode*)c->objectAtIndex(2))->getChildren();



        for (int i = 0; i < 3; i++) {
            cocos2d::CCNode* b = (cocos2d::CCNode*)c2->objectAtIndex(i);

            b->setScale(0);
            b->setRotation(90);

            b->runAction(cocos2d::CCSequence::create(
                cocos2d::CCDelayTime::create(.5 + i * .25),
                cocos2d::CCSpawn::create(
                    cocos2d::CCEaseBackOut::create(
                        cocos2d::CCScaleTo::create(1.25, 1)
                    ),
                    cocos2d::CCEaseBackOut::create(
                        cocos2d::CCRotateTo::create(1.25, 0)
                    ),
                    nullptr
                ),
                nullptr
            ));
        }

        cocos2d::CCNode* pb = (cocos2d::CCNode*)c2->objectAtIndex(3);

        pb->setScale(0);
        pb->setRotation(-90);

        pb->runAction(cocos2d::CCSequence::create(
            cocos2d::CCDelayTime::create(.8),
            cocos2d::CCSpawn::create(
                cocos2d::CCEaseOut::create(
                    cocos2d::CCScaleTo::create(1.25, 1),
                    4
                ),
                cocos2d::CCEaseOut::create(
                    cocos2d::CCRotateTo::create(1.25, 0),
                    4
                ),
                nullptr
            ),
            nullptr
        ));
    }

    {   // title
        cocos2d::CCNode* title = ((cocos2d::CCNode*)c->objectAtIndex(1));

        title->setScale(0);

        title->runAction(cocos2d::CCSequence::create(
            cocos2d::CCDelayTime::create(.25),
            cocos2d::CCEaseBackOut::create(
                cocos2d::CCScaleTo::create(2, 1)
            ),
            nullptr
        ));
    }

    {   // name
        cocos2d::CCNode* t = (cocos2d::CCNode*)c->objectAtIndex(6);
        cocos2d::CCArray* c2 = t->getChildren();

        for (int i = 0; i < t->getChildrenCount(); i++) {
            cocos2d::CCNode* ch = (cocos2d::CCNode*)c2->objectAtIndex(i);

            ch->setScale(0);

            ch->runAction(cocos2d::CCSequence::create(
                cocos2d::CCDelayTime::create(.5 + i * .2),
                cocos2d::CCEaseElasticOut::create(
                    cocos2d::CCScaleTo::create(1, 1)
                ),
                nullptr
            ));
        }
    }

    {   // ground + icons
        cocos2d::CCArray* c2 = ((cocos2d::CCNode*)c->objectAtIndex(0))->getChildren();

        cocos2d::CCNode* ground = (cocos2d::CCNode*)c2->objectAtIndex(1);
        float g_pos = ground->getPositionY();
        cocos2d::CCSize g_size = ground->getContentSize();

        ground->setPositionY(g_pos - g_size.height);

        ground->runAction(cocos2d::CCSequence::create(
            cocos2d::CCDelayTime::create(.5),
            cocos2d::CCEaseExponentialOut::create(
                cocos2d::CCMoveBy::create(2, { 0, g_size.height })
            ),
            nullptr
        ));

        for (int i = 5; i <= 6; i++) {
            cocos2d::CCNode* icons = (cocos2d::CCNode*)c2->objectAtIndex(i);
            icons->setScale(0);

            icons->runAction(cocos2d::CCSequence::create(
                cocos2d::CCDelayTime::create(.5),
                cocos2d::CCEaseExponentialOut::create(
                    cocos2d::CCScaleTo::create(2, 1)
                ),
                nullptr
            ));
        }
    }

    {   // bottom menu
        cocos2d::CCArray* c2 = ((cocos2d::CCNode*)c->objectAtIndex(3))->getChildren();
        int a = ((cocos2d::CCNode*)c->objectAtIndex(3))->getChildrenCount();

        for (int i = 0; i < a - 1; i++) {
            cocos2d::CCNode* b = (cocos2d::CCNode*)c2->objectAtIndex(i);

            b->setScale(0);

            b->runAction(cocos2d::CCSequence::create(
                cocos2d::CCDelayTime::create(1 + .25 * i),
                cocos2d::CCEaseExponentialOut::create(
                    cocos2d::CCScaleTo::create(1, 1)
                ),
                nullptr
            ));

            b->runAction(cocos2d::CCSequence::create(
                cocos2d::CCDelayTime::create(2.2 + .1 * i),
                cocos2d::CCEaseIn::create(
                    cocos2d::CCScaleTo::create(.25, 1.25),
                    4
                ),
                cocos2d::CCEaseBackInOut::create(
                    cocos2d::CCScaleTo::create(.75, 1)
                ),
                nullptr
            ));
        }

        cocos2d::CCNode* chests = (cocos2d::CCNode*)c2->objectAtIndex(a - 1);
        float c_x = chests->getPositionX();

        chests->setPositionX(c_x + 100);

        chests->runAction(cocos2d::CCSequence::create(
            cocos2d::CCDelayTime::create(2),
            cocos2d::CCEaseExponentialOut::create(
                cocos2d::CCMoveBy::create(1, { -100, 0 })
            ),
            nullptr
        ));
    }

    {   // bottom left buttons
        cocos2d::CCArray* c2 = ((cocos2d::CCNode*)c->objectAtIndex(4))->getChildren();

        for (int i = 0; i < 4; i++) {
            cocos2d::CCNode* b = (cocos2d::CCNode*)c2->objectAtIndex(i);

            b->setScale(0);

            b->runAction(cocos2d::CCSequence::create(
                cocos2d::CCDelayTime::create(1.5 + .2 * i),
                cocos2d::CCEaseBackOut::create(
                    cocos2d::CCScaleTo::create(1, 1)
                ),
                nullptr
            ));
        }
    }

    {   // more games & close
        cocos2d::CCArray* c2 = ((cocos2d::CCNode*)c->objectAtIndex(5))->getChildren();

        cocos2d::CCNode* close = (cocos2d::CCNode*)c2->objectAtIndex(1);
        close->setScale(0);

        close->runAction(cocos2d::CCSequence::create(
            cocos2d::CCDelayTime::create(2.5),
            cocos2d::CCEaseExponentialOut::create(
                cocos2d::CCScaleTo::create(1.25, 1)
            ),
            nullptr
        ));

        cocos2d::CCNode* moregames = (cocos2d::CCNode*)c2->objectAtIndex(0);
        moregames->setScale(0);
        moregames->setRotation(90);

        moregames->runAction(cocos2d::CCSequence::create(
            cocos2d::CCDelayTime::create(2),
            cocos2d::CCSpawn::create(
                cocos2d::CCEaseBackOut::create(
                    cocos2d::CCScaleTo::create(1, 1)
                ),
                cocos2d::CCEaseBackOut::create(
                    cocos2d::CCRotateTo::create(1, 0)
                ),
                nullptr
            ),
            nullptr
        ));
    }

    return true;
}

GDMAKE_MAIN {
    MoreOptionsLayer::addToggle = reinterpret_cast<decltype(MoreOptionsLayer::addToggle)>(base + 0x1DF6B0);

    return true;
}

GDMAKE_UNLOAD {}
