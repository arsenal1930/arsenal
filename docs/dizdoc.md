# Arsenal 1930

## Жанр и синопсис
2Д экшен-РПГ с боёвкой из AUT.

Сэттинг выбирается.

## Стиль игры
TODO

## Системы и механики
### Системы
#### Передвижение
Передвижение осуществляется нажатием клавиш.
Перемещение осуществляется в основном ходьбой.
Нажатие клавиши ускорения переключает режим на бег.
Рывок на клавишу рывка 
Некоторые оружия имеют модификации рывка(телепортацию, замедление времени и пр.).
##### Логика
Нажатие клавиш прибавляет к значению направления сущности 1 или -1 в зависимости от направления. 

Значений направления 2:
 - по вертикали(`InputY`) 
 - по горизонтали(`InputX`)

Пример движения вперёд по горизонтали:

```
InputX += 1.0f; // прибавляем к значению направления сущности
                // (располагается внутри функции движения)
```

Затем спрайт игрока перемещается на `InputX`(`InputY`) умноженное на значение скорости пикселей. 
После этого проверются столкновения с преградами, при столкновении 

#### Здоровье
Каждая сущность, за исключением меня, имеет очки здоровья, очки рэнжи.
Количество очков здоровья и рэнджи напрямую зависит от уровня персонажа.

#### Боёвка
Боёвка работает как в AUT с поправками на то, что игра 2D. 
Атаки делаются в направлении взгляда персонажа, взгляд же контроллируется AxisInput.

Есть несколько видов атак:
 - Обычная атака - представляет из себя квадратный хитбокс, 
   появляющийся зачастую около атакующего. Обычно замедляет 
   попавшего в зону его действия нанося урон,может иметь другие свойства. 
   Имеет отношение непосредственно к атакующему, как удар кулаком например.
 - Комбо-атака - представляет из себя череду обычных атак без кулдауна, 
   которые сменяют друг друга до определённого числа нажатий, 
   после конца комбо-атаки начинается кулдаун.
 - Дальняя атака - запускает проджектайл в направлении взгляда персонажа, 
   который наносит урон и может иметь другие свойства. 
   Не относится непосредственно к самому персонажу.
 - Повторяющаяся атака - атака состоящая из нескольких атакующих спрайтов, 
   они следуют друг-за другом как в плане последовательности появления, 
   так и в направлении появления. Не относится непосредственно к самому персонажу.
   Например линия из ледяных кристаллов, вырос один, за ним следующий,
   потом следующий и так до определённого количества кристаллов\атак.
 - Удалённая атака - обычная атака, которая происходит на расстоянии от персонажа. 
   Не относится непосредственно к самому персонажу.
 - Атака по области(АОЕ, АУЕ) - наносит урон по области и может иметь урон.

Атаки могут принадлежать к нескольким типам сразу.

Каждое оружие имеет:
 - набор атак, у которых есть свой к\д 
 - эффекты накладываемые как на носителя оружия, так и на попавшего в
   область(коллайдер) действия атаки
 - количество восполняемой рэнжи и очков жизни каждой атаки.

#### Экономика
В игре будет система заводов, магазинов и пр. И вся соответствующая продукция будет распределена между учреждениями.

### Механики
#### Взаимодействие
Персонаж, подойдя к предмету, НИП или интерактивному событию, нажав клавишу действия.

Провзаимодействовав с предметом, персонаж совершит действие либо ассоциирующееся с предметом(например подобрать палку), либо действие специально заданное(например пнуть палку, а не подобрать).

Провзаимодействовав с НИП - начинается диалог или битва.

#### Природные явления или погодные условия