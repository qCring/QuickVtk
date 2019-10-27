var nav = {
  element: undefined,
  visible: false,

  toggle: function () {
    console.log("toggle");

    if (this.element == undefined) {
      this.element = document.getElementById ('nav-content');
    }

    if (this.element != undefined) {
      this.visible = !this.visible;

      if (this.visible) {
        this.element.classList.add ('visible');
      } else {
        this.element.classList.remove ('visible');
      }
    }
  }
}
