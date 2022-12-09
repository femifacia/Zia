<?php

$writers = [
    [
        'name' => 'Fèmi Facia',
        'mail' => 'femi.facia@epitech.eu',
    ],
    [
        'name' => 'Georges Houmbadji',
        'mail' => 'georges.houmbadji@epitech.eu',
    ],
    [
        'name' => 'Damia Tobossi',
        'mail' => 'damia.tobossi@epitech.eu',
    ],
    [
        'name' => 'Sergino Gounoukperou',
        'mail' => 'sergino@gounoukperou@epitech.eu',
    ],
    [
        'name' => 'Francesca Attindehou',
        'mail' => 'francesca.attindehou@epitech.eu',
    ],
];

$mybooks = [
    [
        'name' => 'Jane Eyre',
        'content' => '',
        'writer' => 'Charlotte Bronte',
    ],
    [
        'name' => 'L attrape coeur',
        'content' => '',
        'writer' => 'J. D. Salinger',
    ],
    [
        'name' => 'Ne tirez pas sur l oiseau moqueur',
        'content' => '',
        'writer' => 'Harper Lee',
    ],
    [
        'name' => 'Gatsby le Magnifique',
        'content' => '',
        'writer' => 'F. Scott Fitzgerald',
    ],
    [
        'name' => 'Les Hauts de Hurlevent ',
        'content' => '',
        'writer' => 'Emily Bronte',
    ],
];

function our_books(array $book) : string
{
    $content = '';
    $content .= '<p><h5>' . $book['name'] . '</h5>';
    $content .= '<div>' . $book['content'] . '</div>';
    $content .= '<i>' . $book['writer'] . '</i></p>';
    return $content;
}

function our_writers(array $write) : string
{
    $content = '<p>';
    $content .= '<h5>' . $write['name'] . '</h5>';
    $content .= '<div>' . $write['mail'] . '</div></p>' ;
    return $content;
}