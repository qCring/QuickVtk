var nav = {
  content: undefined,
  icon: undefined,
  visible: false,

  toggle: function () {

    if (this.content == undefined) {
      this.content = document.getElementById ('nav-content');
    }

    if (this.icon == undefined) {
      this.icon = document.getElementById ('nav-toggle-icon');
    }

    if (this.content != undefined && this.icon != undefined) {
      this.visible = !this.visible;

      if (this.visible) {
        this.content.classList.add ('visible');
        this.icon.className = "fas fa-times";
      } else {
        this.content.classList.remove ('visible');
        this.icon.className = "fas fa-grip-lines";
      }
    }
  }
}
