use cursive::theme::{BorderStyle, Palette};
use cursive::traits::{Nameable, With};
use cursive::views::{Checkbox, Dialog, EditView, ListView, TextView};
use cursive::{Cursive, CursiveExt};

struct CatsayOptions<'a> {
    message: &'a str,
    dead: bool,
}

fn main() {
    let mut siv = Cursive::default();

    let theme = cursive::theme::Theme {
        shadow: false,
        borders: BorderStyle::Simple,
        palette: Palette::default().with(|palette| {
            use cursive::theme::Color::*;
            use cursive::theme::PaletteColor::*;
            palette[Background] = TerminalDefault;
        }),
    };
    siv.set_theme(theme);
    input_step(&mut siv);
    siv.run();
}

fn input_step(siv: &mut Cursive) {
    let title = "Please fill out the form for the cat";
    let list_view = ListView::new()
        .child("Message:", EditView::new().with_name("message"))
        .child("Dead?", Checkbox::new().with_name("dead"))
        .child("Fish?", TextView::new("Caterpiller"));
    let dialog = Dialog::new().title(title).content(list_view);

    siv.add_layer(dialog.button("OK", |s| {
        let message = s
            .call_on_name("message", |t: &mut EditView| t.get_content())
            .unwrap();
        let is_dead = s
            .call_on_name("dead", |t: &mut Checkbox| t.is_checked())
            .unwrap();
        let options = CatsayOptions {
            message: &message,
            dead: is_dead,
        };
        result_step(s, &options)
    }));
}

fn result_step(siv: &mut Cursive, options: &CatsayOptions) {
    let eye = if options.dead { "x" } else { "o" };

    let cat_text = format!(
        "{msg}
  \\
   \\
    /\\_/\\
   ( {eye} {eye} )
   =( I )=",
        msg = options.message,
        eye = eye
    );

    siv.pop_layer();
    let db = Dialog::around(TextView::new(cat_text));
    siv.add_layer(db.title("The cat says...").button("OK", |s| s.quit()));
}
