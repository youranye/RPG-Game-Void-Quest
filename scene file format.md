# Scene File Format

The scene format is a restricted subset of Markdown, used to define the scenes in the game's story, including story text and battle scenes. The format is described in BNF notation below, as well as with provided examples.

## Terminology

### Line

A *line* is the base unit of scene files, consisting of three parts: a prefix determining the type of line, an optional bracket-enclosed attribute, and text. Whitespace between these parts are ignored. Whitespace between lines is also ignored.

#### Example

```
# [battle] battle
```

The following prefixes are defined:

|Prefix|In Code|Description|
|-|-|-|
|None|`Text`|Normal text|
|`#`|`H1`|A header. Used for the name of the|
|`##`|`H2`|A secondary header|
|`-`|`Option`|A list item|

### Name

The name of a scene is 

### Key

The key of a scene is a string which uniquely identifies the scene. In the case of files, this consists of the path of the file relative to the root of the resource directory without the `.md` extension, followed by a `#`, followed by the name of the scene.

#### Example

Given the following scene, located in `<resource directory>/myscene.md`

```
# MyScene

My flavor text

## Options
```

The key of the scene would be `myscene#MyScene`.

### Relative key

For ergonomic reasons, scenes within the same file can be referenced with *relative keys*, omitting the file name.

## BNF

### Lines

```ebnf
text_line   := (* Omitted *) ;
h1_line     := (* Omitted *) ;
h2_line     := (* Omitted *) ;
option_line := (* Omitted *) ;
```

See section on terminology above

### Narrative Scenes

```ebnf
narrative_scene :=
    h1_line (* Used for the name of the scene *)
    { text_line } (* Flavor text *)
    h2_line
    { option_line } (* Used as the options of the scene *)
    ;
```

Note: Option lines for narrative scenes are then split into two parts: the option text and the key of the scene to go to for that option. The two parts are divided by an arrow (` -> `).

#### Example

```
# MyScene

Some flavor text

## Options
 - option 1 -> #myotherscene
 - option 2 -> myotherfile#anotherScene
```

### Battle Scenes

```ebnf
battle_scene :=
    h1_line (* Used for the name of the scene *)
    h2_line
    option_line (* Used as name of the enemy in the scene *)
    ;
```

Note: The H1 line uses the attribute `[battle]` to distinguish it from narrative scenes

#### Example

```
# MyBattleScene

## Enemy
 - Dragon
```